#include "physics_system.h"

#include "core/ecs/world.h"
#include "core/world/physics/collision_component.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include <raymath.h>

#include <algorithm>

namespace otb
{
void PhysicsSystem::update(World* world)
{
    static constexpr float velocity_damping_coeff = 0.95f;
    static constexpr float g = 9.8f;
    static constexpr float eps = 0.001f;

    for (auto it = world->components_begin<VelocityComponent>(); it != world->components_end<VelocityComponent>(); ++it)
    {
        auto* transform_component = it->entity->get_component<TransformComponent>();
        OTB_ASSERT(transform_component != nullptr);

        Vector3 target_location = transform_component->transform.translation;
        Vector3 updated_velocity = it->velocity;

        if (it->apply_gravity)
            updated_velocity.y -= g * world->fixed_frame_time;
        updated_velocity *= velocity_damping_coeff;

        target_location += Vector3Scale(updated_velocity, world->fixed_frame_time);

        Vector3 pos_to_target;
        float pos_to_target_distance;
        Ray movement_ray;
        const auto update_context = [&]
        {
            pos_to_target = target_location - transform_component->transform.translation;
            pos_to_target_distance = Vector3Length(pos_to_target);
            movement_ray = {
                .position = transform_component->transform.translation,
                .direction = Vector3Scale(pos_to_target, 1.f / pos_to_target_distance),
            };
        };
        update_context();

        bool has_collision = true;
        do
        {
            has_collision = false;
            for (auto it = world->components_begin<CollisionComponent>(); it != world->components_end<CollisionComponent>(); ++it)
            {
                RayCollision collision = it->test_fn(movement_ray);
                if (collision.hit && collision.distance < pos_to_target_distance)
                {
                    it->callback_fn(collision.point);
                    float post_hit_rate = 1 - collision.distance / pos_to_target_distance;
                    target_location = collision.point + collision.normal * eps;
                    updated_velocity -= Vector3Project(updated_velocity, collision.normal);
                    target_location += updated_velocity * post_hit_rate * world->fixed_frame_time;
                    OTB_ASSERT(updated_velocity.y >= -100);
                    has_collision = true;
                    update_context();
                }
            }
        } while (has_collision);

        transform_component->transform.translation = target_location;
        it->velocity = updated_velocity;
    }
}
}