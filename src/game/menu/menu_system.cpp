#include "menu_system.h"

#include "core/ecs/component.h"
#include "core/ecs/world.h"

#include "game/menu/menu_button_component.h"
#include "game/menu/menu_layer_component.h"
#include "game/world_creator.h"

#include <raylib.h>
#include <raymath.h>

#include <algorithm>

namespace game
{
namespace
{
struct MenuControllerComponent : public otb::Component
{
    ~MenuControllerComponent() override = default;

    std::unique_ptr<otb::World> sub_world;
    otb::InternedString sub_world_path = otb::InternedString::get_empty();

    std::vector<otb::InternedString> events;
};
}

void MenuSystem::init(otb::World* world)
{
    world->get_world_entity()->add_component(new MenuControllerComponent());
}

void MenuSystem::collect_events(otb::World* world)
{
    HideCursor();

    auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();
    if (menu_component->sub_world != nullptr)
        return;

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;
    
    for (auto it = world->components_begin<MenuButtonComponent>(); it != world->components_end<MenuButtonComponent>(); ++it)
    {
        const auto* layer = it->entity->get_component<MenuLayerComponent>();
        OTB_ASSERT(layer != nullptr);
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

void MenuSystem::process_events(otb::World* world)
{
    using namespace otb;

    auto* menu_component = world->get_world_entity()->get_component<MenuControllerComponent>();

    static const InternedString LVL_1_EVENT("go_level.lvl1");
    static const InternedString LVL_2_EVENT("go_level.lvl2");
    static const InternedString LVL_1_ASSET("/lvl1.vs");
    static const InternedString LVL_2_ASSET("/lvl2.vs");

    for (const auto event : std::exchange(menu_component->events, {}))
    {
        if (event == LVL_1_EVENT)
        {
            menu_component->sub_world = create_world(LVL_1_ASSET);
            menu_component->sub_world_path = LVL_1_ASSET;
        }
        else if (event == LVL_2_EVENT)
        {
            menu_component->sub_world = create_world(LVL_2_ASSET);
            menu_component->sub_world_path = LVL_2_ASSET;
        }
    }
    if (IsKeyPressed(KEY_R) && menu_component->sub_world)
    {
        menu_component->sub_world.reset();
        menu_component->sub_world = create_world(menu_component->sub_world_path);
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
    std::transform(world->components_begin<MenuLayerComponent>(), world->components_end<MenuLayerComponent>(), std::back_inserter(layers), [](const auto& v) {
        return std::cref(v);
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