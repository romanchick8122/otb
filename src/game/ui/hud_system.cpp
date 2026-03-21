#include "hud_system.h"

#include "core/ecs/world.h"
#include "core/render/texture_asset.h"

#include "game/character/character_component.h"

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
}
void HudSystem::render_hud(otb::World* world, float)
{
    const CharacterComponent* character_component = &*world->components_begin<CharacterComponent>();
    if (character_component->movement_state == CharacterComponent::MovementState::AIMING)
    {
        render_scope();
    }
}
}
