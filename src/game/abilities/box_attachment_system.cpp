#include "box_attachment_system.h"

#include "core/ecs/world.h"
#include "core/ecs/component.h"
#include "core/math/transform_utils.h"
#include "core/render/camera_component.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/abilities/box_attachment_ability_component.h"
#include "game/box/box_component.h"
#include "game/box/box_system.h"
#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"

#include <raymath.h>

namespace game
{
void BoxAttachmentSystem::process_ability_activation(otb::World* world)
{
    using namespace otb;

    const auto* character_component = &*world->components_begin<CharacterComponent>();
    const auto* character_input_receiver = world->components_begin<CharacterComponent>()->entity->get_component<InputReceiverComponent>();
    BoxAttachmentAbilityComponent* ability = character_input_receiver->entity->get_component<BoxAttachmentAbilityComponent>();
    if (ability == nullptr) [[unlikely]]
    {
        ability = new BoxAttachmentAbilityComponent();
        character_input_receiver->entity->add_component(ability);
    }

    if (character_input_receiver->extra_actions.count(InputReceiverComponent::ActionNames::ability) == 0)
    {
        return;
    }

    // Detach
    if (ability->attached_box != nullptr)
    {
        ability->attached_box = nullptr;
        return;
    }

    if (character_component->movement_state != CharacterComponent::MovementState::AIMING)
    {
        return;
    }

    // Attach
    const otb::CameraComponent* camera = world->get_world_entity()->get_component<CameraComponent>();
    const Ray camera_ray {
        .position = camera->camera.position,
        .direction = Vector3Normalize(camera->camera.target - camera->camera.position),
    };

    std::pair<RayCollision, BoxComponent*> best_hit{ {}, nullptr };
    for (auto box_it = world->components_begin<BoxComponent>(); box_it != world->components_end<BoxComponent>(); ++box_it)
    {
        if (box_it->entity == character_input_receiver->entity)
        {
            continue;
        }

        const BoundingBox box = TransformUtils::get_box(box_it->entity->get_component<TransformComponent>()->transform);
        RayCollision collision = GetRayCollisionBox(camera_ray, box);
        if (!collision.hit)
        {
            continue;
        }
        if (best_hit.second == nullptr || best_hit.first.distance > collision.distance)
        {
            best_hit = { collision, &*box_it};
        }
    }
    if (best_hit.second != nullptr && best_hit.second->type == BoxComponent::BoxType::DYNAMIC)
    {
        ability->attached_box = best_hit.second;
        ability->local_space_attachment_position = TransformUtils::apply_inverse_transform(best_hit.second->entity->get_component<TransformComponent>()->transform, best_hit.first.point);
    }
}

void BoxAttachmentSystem::process_ability(otb::World* world)
{
    using namespace otb;
    auto* box_sc = world->get_world_entity()->get_component<BoxSingleComponent>();
    const auto* character_component = &*world->components_begin<CharacterComponent>();
    const Vector3 character_position = character_component->entity->get_component<TransformComponent>()->transform.translation;
    const auto* character_velocity_component = character_component->entity->get_component<VelocityComponent>();
    if (abs(character_velocity_component->velocity.x) < EPSILON && abs(character_velocity_component->velocity.z) < EPSILON)
    {
        return;
    }
    const Vector2 character_velocity_proj = Vector2Normalize({character_velocity_component->velocity.x, character_velocity_component->velocity.z});
    for (auto it = world->components_begin<BoxAttachmentAbilityComponent>(); it != world->components_end<BoxAttachmentAbilityComponent>(); ++it)
    {
        if (it->attached_box != nullptr)
        {
            const Vector3 to_box_direction = it->attached_box->entity->get_component<TransformComponent>()->transform.translation - character_position;
            it->pulling = Vector2DotProduct({to_box_direction.x, to_box_direction.z}, character_velocity_proj) < 0;
            if (it->pulling)
            {
                box_sc->request_one_frame_attachment(it->attached_box);
            }
        }
    }
}

void BoxAttachmentSystem::debug_draw(otb::World* world, float)
{
    using namespace otb;

    BoxAttachmentAbilityComponent* ability = world->components_begin<CharacterComponent>()->entity->get_component<BoxAttachmentAbilityComponent>();
    if (ability == nullptr) [[unlikely]]
    {
        return;
    }
    if (ability->attached_box == nullptr)
    {
        return;
    }

    const Vector3 from = ability->entity->get_component<TransformComponent>()->transform.translation;
    const Vector3 to = TransformUtils::apply_transform(ability->attached_box->entity->get_component<TransformComponent>()->transform, ability->local_space_attachment_position);
    DrawLine3D(from, to, YELLOW);
}
}