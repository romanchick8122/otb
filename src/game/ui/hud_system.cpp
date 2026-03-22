#include "hud_system.h"

#include "core/ecs/world.h"
#include "core/render/texture_asset.h"
#include "core/ui/ui_utils.h"

#include "game/character/character_component.h"
#include "game/inventory/inventory_component.h"

#include <raylib.h>
#include <raymath.h>

namespace game
{
namespace
{
void render_scope()
{
    static const auto scope = otb::AssetUtils::get_asset<otb::TextureAsset>("/ui/scope.png");
    static constexpr float SCOPE_TEXTURE_SIZE = 581;
    static constexpr float SCOPE_TARGET_SIZE = 100;

    DrawTextureEx(scope->texture, Vector2{GetScreenWidth() / 2.f, GetScreenHeight() / 2.f} - (Vector2{SCOPE_TARGET_SIZE, SCOPE_TARGET_SIZE} * 0.5f), 0, SCOPE_TARGET_SIZE / SCOPE_TEXTURE_SIZE, WHITE);
}

auto& get_item_icons()
{
    static const std::unordered_map<otb::InternedString, otb::Asset<otb::TextureAsset>> item_icons = {
        { otb::InternedString::get_empty(), otb::AssetUtils::get_asset<otb::TextureAsset>("/ui/inventory/icons/lock.png") },
        { "thread_n_needle", otb::AssetUtils::get_asset<otb::TextureAsset>("/ui/inventory/icons/needle.png") },
        { "umbrella", otb::AssetUtils::get_asset<otb::TextureAsset>("/ui/inventory/icons/umbrella.png") },
    };
    return item_icons;
}

void render_active_item(const InventoryComponent* inventory)
{
    using namespace otb;

    static const auto bg = AssetUtils::get_asset<TextureAsset>("/ui/inventory/active_item_bg.png");

    static const Vector2 norm_pos { -0.8f, 0.8f };
    static const float target_height = 0.2f;

    const Vector2 texture_size { static_cast<float>(bg->texture.width), static_cast<float>(bg->texture.height) };
    const Vector2 norm_size = { UIUtils::get_norm_target_width(texture_size, target_height), target_height };
    const Rectangle norm_target_rect = UIUtils::rect_from_min_max(norm_pos - norm_size / 2.f, norm_pos + norm_size / 2.f);
    const Rectangle screen_target_rect = UIUtils::normalized_to_screen(norm_target_rect);

    const auto& item_icon_it = get_item_icons().at(inventory->active_item);
    OTB_ASSERT(item_icon_it != nullptr);

    DrawTexturePro(bg->texture, UIUtils::get_texture_rect(bg->texture), screen_target_rect, {}, 0.f, WHITE);
    DrawTexturePro(item_icon_it->texture, UIUtils::get_texture_rect(item_icon_it->texture), screen_target_rect, {}, 0.f, WHITE);
}

void render_inventory(const InventoryComponent* inventory)
{
    using namespace otb;

    static const auto bg = AssetUtils::get_asset<TextureAsset>("/ui/inventory/inventory_menu.png");
    static const auto highlight = AssetUtils::get_asset<TextureAsset>("/ui/inventory/selector.png");

    static constexpr size_t SECTOR_COUNT = 3.f;
    static constexpr float WHEEL_RADIUS = 1.f;
    static constexpr float ITEM_RADIUS = .3f;
    static constexpr float ITEM_SIZE = .25f;

    render_active_item(inventory);

    if (!inventory->hud_open)
    {
        return;
    }

    const Vector2 texture_size { static_cast<float>(bg->texture.width), static_cast<float>(bg->texture.height) };
    const Vector2 norm_size = { UIUtils::get_norm_target_width(texture_size, WHEEL_RADIUS), WHEEL_RADIUS };
    const Rectangle norm_target_rect = UIUtils::rect_from_min_max(norm_size / -2.f, norm_size / 2.f);
    const Rectangle screen_target_rect_raw = UIUtils::normalized_to_screen(norm_target_rect);
    const Vector2 origin = Vector2{screen_target_rect_raw.width, screen_target_rect_raw.height} / 2.f;
    const Rectangle screen_target_rect {
        .x = screen_target_rect_raw.x + origin.x,
        .y = screen_target_rect_raw.y + origin.y,
        .width = screen_target_rect_raw.width,
        .height = screen_target_rect_raw.height,
    };
    
    DrawTexturePro(bg->texture, UIUtils::get_texture_rect(bg->texture), screen_target_rect, origin, 0.f, WHITE);

    if (inventory->hud_highlighted_sector != std::string::npos)
    {
        const float rotation_angle = (2.f * PI) * static_cast<float>(inventory->hud_highlighted_sector) / static_cast<float>(SECTOR_COUNT);
        DrawTexturePro(highlight->texture, UIUtils::get_texture_rect(highlight->texture), screen_target_rect, origin, rotation_angle / DEG2RAD, WHITE);
    }

    OTB_ASSERT(inventory->items.size() < SECTOR_COUNT);
    const Vector2 item_origin = Vector2{ UIUtils::get_norm_target_width({1.f, 1.f}, ITEM_SIZE / 2.f), ITEM_SIZE / 2.f } * UIUtils::get_screen_size() / 2.f;
    for (size_t i = 0; i < SECTOR_COUNT; ++i)
    {
        const float rotation_angle = 2.f * PI * static_cast<float>(i) / SECTOR_COUNT;
        const InternedString sector_item = (i < inventory->items.size()) ? inventory->items[i] : InternedString::get_empty();
        const auto icon_it = get_item_icons().at(sector_item);
        const float x_raw = sin(rotation_angle) * ITEM_RADIUS;
        const Rectangle norm_rect = {
            .x = (x_raw > 0.f ? 1.f : -1.f) * UIUtils::get_norm_target_width({1.f, 1.f}, abs(x_raw)),
            .y = cos(rotation_angle) * ITEM_RADIUS,
            .width = UIUtils::get_norm_target_width({1.f, 1.f}, ITEM_SIZE),
            .height = ITEM_SIZE,
        };
        const Rectangle screen_rect_raw = UIUtils::normalized_to_screen(norm_rect);
        const Rectangle screen_rect {
            .x = screen_rect_raw.x,
            .y = screen_rect_raw.y,
            .width = screen_rect_raw.width,
            .height = screen_rect_raw.height,
        };
        DrawTexturePro(icon_it->texture, UIUtils::get_texture_rect(icon_it->texture), screen_rect, item_origin, 0.f, WHITE);
    }
}
}
void HudSystem::render_hud(otb::World* world, float)
{
    const CharacterComponent* character_component = &*world->components_begin<CharacterComponent>();
    if (character_component->movement_state == CharacterComponent::MovementState::AIMING)
    {
        render_scope();
    }
    render_inventory(character_component->entity->get_component<InventoryComponent>());
}
}
