#include "fan_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/abilities/fan_component.h"
#include "game/character/character_component.h"

#include "raymath.h"

namespace game
{
void FanSystem::apply_velocity(otb::World* world)
{
    using namespace otb;
    const auto* character_component = &*world->components_begin<CharacterComponent>();
    auto* character_velocity = character_component->entity->get_component<VelocityComponent>();
    const auto* character_transform = character_component->entity->get_component<TransformComponent>();
    for (auto it = world->components_begin<FanComponent>(); it != world->components_end<FanComponent>(); ++it)
    {
        const auto* box_transform = it->entity->get_component<TransformComponent>();
        const Vector3 character_box_space = TransformUtils::apply_inverse_transform(box_transform->transform, character_transform->transform.translation);
        static constexpr BoundingBox default_bb {
            .min = {-.5f, -.5f, -.5f},
            .max = {.5f, .5f, .5f},
        };
        if (!TransformUtils::is_point_in_bounding_box(character_box_space, default_bb))
        {
            continue;
        }

        const Vector3 fan_forward = Vector3RotateByQuaternion({1, 0, 0}, it->entity->get_component<TransformComponent>()->transform.rotation) * it->power;
        // xz reset each frame, y is persistent
        character_velocity->velocity.x += fan_forward.x;
        character_velocity->velocity.y += fan_forward.y * world->fixed_frame_time;
        character_velocity->velocity.z += fan_forward.z;
    }
}
}