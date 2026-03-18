#include "fan_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/abilities/fan_component.h"
#include "game/abilities/fan_control_button_component.h"
#include "game/box/box_component.h"
#include "game/character/character_component.h"

#include "raymath.h"

namespace game
{
void FanSystem::init(otb::World* world)
{
    for (auto it = world->components_begin<FanControlButtonComponent>(); it != world->components_end<FanControlButtonComponent>(); ++it)
    {
        auto* fan_component = world->get_entity(it->target_entity)->get_component<FanComponent>();
        OTB_ASSERT(fan_component != nullptr);
        fan_component->controller = &*it;
    }
}

void FanSystem::update_controllers(otb::World* world)
{
    const auto* character_component = &*world->components_begin<CharacterComponent>();
    const auto* character_box = character_component->entity->get_component<BoxComponent>();
    auto* this_frame_pressed = character_box->rests_on == nullptr ? nullptr : character_box->rests_on->entity->get_component<FanControlButtonComponent>();

    if (this_frame_pressed != nullptr && !this_frame_pressed->prev_frame_pressed)
    {
        this_frame_pressed->enabled = !this_frame_pressed->enabled;
    }

    for (auto it = world->components_begin<FanControlButtonComponent>(); it != world->components_end<FanControlButtonComponent>(); ++it)
    {
        it->prev_frame_pressed = &*it == this_frame_pressed;
    }
}

void FanSystem::apply_velocity(otb::World* world)
{
    using namespace otb;
    const auto* character_component = &*world->components_begin<CharacterComponent>();
    auto* character_velocity = character_component->entity->get_component<VelocityComponent>();
    const auto* character_transform = character_component->entity->get_component<TransformComponent>();
    for (auto it = world->components_begin<FanComponent>(); it != world->components_end<FanComponent>(); ++it)
    {
        if (it->controller != nullptr && !it->controller->enabled)
        {
            continue;
        }

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