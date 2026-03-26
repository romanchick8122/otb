#include "menu_system.h"

#include "core/ecs/component.h"
#include "core/ecs/world.h"

#include "game/menu/menu_button_component.h"
#include "game/menu/menu_layer_component.h"
#include "game/menu/upstream_interaction_component.h"
#include "game/world_creator.h"

#include <raylib.h>
#include <raymath.h>

#include <algorithm>

namespace game
{
namespace
{
static const otb::InternedString MAIN_MENU_GROUP("main_menu");

struct MenuControllerComponent : public otb::Component
{
    ~MenuControllerComponent() override = default;

    std::unique_ptr<otb::World> sub_world;
    otb::InternedString sub_world_path = otb::InternedString::get_empty();

    std::vector<otb::InternedString> events;
    otb::InternedString group = MAIN_MENU_GROUP;
};
}

void MenuSystem::init(otb::World* world)
{
    world->get_world_entity()->add_component(new MenuControllerComponent());
}

void MenuSystem::reset_curstor(otb::World* world)
{
    auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();
    if (menu_component->sub_world != nullptr)
    {
        SetMousePosition(GetRenderWidth() / 2, GetRenderHeight() / 2);
    }
}

namespace
{
static const otb::InternedString RESTART_LEVEL_EVENT("restart_level");
}

void MenuSystem::collect_events(otb::World* world)
{
    HideCursor();

    auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();

    // Always active events
    if (menu_component->sub_world != nullptr && IsKeyPressed(KEY_R))
    {
        menu_component->events.push_back(RESTART_LEVEL_EVENT);
    }

    if (menu_component->sub_world != nullptr)
        return;

    // Menu only events
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;
    
    for (auto it = world->components_begin<MenuButtonComponent>(); it != world->components_end<MenuButtonComponent>(); ++it)
    {
        const auto* layer = it->entity->get_component<MenuLayerComponent>();
        OTB_ASSERT(layer != nullptr);
        if (layer->group != menu_component->group)
        {
            continue;
        }
        const Rectangle rect = layer->get_screen_space_rect();
        const Vector2 mouse_pos = GetMousePosition();
        if (mouse_pos.x > rect.x && mouse_pos.y > rect.y && mouse_pos.x < rect.x + rect.width && mouse_pos.y < rect.y + rect.height)
        {
            menu_component->events.emplace_back(it->on_click);
        }
    }
}

void MenuSystem::subworld_update_fixed(otb::World* world)
{
    const auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();
    if (menu_component->sub_world != nullptr)
        menu_component->sub_world->fixed_update();
}

void MenuSystem::collect_subworld_events(otb::World* world)
{
    auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();

    if (menu_component->sub_world != nullptr)
    {
        auto* sub_events = menu_component->sub_world->get_world_entity()->get_component<UpstreamInteractionComponent>();
        std::copy(sub_events->events.begin(), sub_events->events.end(), std::back_inserter(menu_component->events));
        sub_events->events.clear();
    }
}

void MenuSystem::process_events(otb::World* world)
{
    using namespace otb;

    auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();

    static const InternedString GO_MAIN_MENU_EVENT("go_main_menu");

    for (const auto event : std::exchange(menu_component->events, {}))
    {
        std::string_view event_view(event.c_str());
        if (event_view.starts_with("set_menu_group."))
        {
            menu_component->group = InternedString(event.c_str() + 15);
        }
        else if (event_view.starts_with("go_level."))
        {
            menu_component->sub_world_path = InternedString(std::format("/levels/{}.vs", event.c_str() + 9).c_str());
            menu_component->sub_world = create_world(menu_component->sub_world_path);
        }
        else if (event == GO_MAIN_MENU_EVENT)
        {
            menu_component->sub_world = nullptr;
            menu_component->group = MAIN_MENU_GROUP;
        }
        else if (event == RESTART_LEVEL_EVENT)
        {
            menu_component->sub_world.reset();
            menu_component->sub_world = create_world(menu_component->sub_world_path);
        }
    }
}

void MenuSystem::render_menu(otb::World* world, float)
{
    using namespace otb;

    const auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();
    if (menu_component->sub_world != nullptr)
        return;

    BeginDrawing();

    std::vector<std::reference_wrapper<const MenuLayerComponent>> layers;
    std::copy_if(world->components_begin<MenuLayerComponent>(), world->components_end<MenuLayerComponent>(), std::back_inserter(layers), [menu_component](const MenuLayerComponent& v) {
        return v.group == menu_component->group;
    });
    std::sort(layers.begin(), layers.end(), [](const auto... l){
        return (l.get().z_order < ...);
    });

    for (auto layer : layers)
    {
        const Texture2D texture = layer.get().texture->texture;
        const Rectangle source { 0.f, 0.f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
        const Rectangle destination = layer.get().get_screen_space_rect();
        DrawTexturePro(layer.get().texture->texture, source, destination, {}, 0, WHITE);
    }

    // Cursor
    {
        static constexpr float MOUSE_CURSOR_SIZE = 25.f;

        static Asset<TextureAsset> cursor = AssetUtils::get_asset<TextureAsset>(InternedString("/ui/scope.png"));
        static Rectangle source_rect { 0.f, 0.f, static_cast<float>(cursor->texture.width), static_cast<float>(cursor->texture.height) };
        const Vector2 mouse_pos = GetMousePosition();
        const Rectangle destination_rect {mouse_pos.x - MOUSE_CURSOR_SIZE / 2.f, mouse_pos.y - MOUSE_CURSOR_SIZE / 2.f, MOUSE_CURSOR_SIZE, MOUSE_CURSOR_SIZE };
        DrawTexturePro(cursor->texture, source_rect, destination_rect, {}, 0, WHITE);
    }

    EndDrawing();
}

void MenuSystem::subworld_update(otb::World* world, float dt)
{
    const auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();
    if (menu_component->sub_world != nullptr)
        menu_component->sub_world->normal_update(dt);
}
}