#include "character_system.h"

#include "core/ecs/world.h"
#include "core/render/camera_component.h"
#include "core/render/model_component.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"

#include "raymath.h"

namespace game
{
void CharacterSystem::update_camera(otb::World* world, float dt)
{
    using namespace otb;

    Camera3D desired_camera = [world]
    {
        CharacterComponent* character = nullptr;
        for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
        {
            OTB_ASSERT(character == nullptr);
            character = &*it;
        }
        const Transform& character_transform = character->entity->get_component<TransformComponent>()->transform;
        Vector3 desired_position =
            character_transform.translation +
            Vector3RotateByQuaternion({-1, 0, 0}, character_transform.rotation) * character->camera_follow_distance +
            Vector3{0, character->camera_follow_offset, 0};
        return Camera3D {
            .position = desired_position,
            .target = character_transform.translation,
            .up = {0, 1, 0},
            .fovy = 90,
            .projection = CAMERA_PERSPECTIVE,
        };
    }();
    
    CameraComponent* camera = world->get_world_entity()->get_component<otb::CameraComponent>();

    static constexpr float MAX_CAMERA_SPEED = 50.f;                  // m/s
    static constexpr float MAX_CAMERA_ANGULAR_SPEED = 3.f;          // rad/s
    static constexpr float MAX_CAMERA_FOVY_CHANGE = 30.f;   // deg/s

    // POSITION
    {
        const Vector3 old_to_new_position = desired_camera.position - camera->camera.position;
        const float distance = Vector3Length(old_to_new_position);
        if (distance > EPSILON)
        {
            const float travel_distance = std::min(distance, MAX_CAMERA_SPEED * dt);
            const Vector3 travel_vector = old_to_new_position / distance * travel_distance;
            camera->camera.position += travel_vector;
        }
    }
    // TARGET
    {
        const Vector3 old_camera_forward = Vector3Normalize(camera->camera.target - camera->camera.position);
        const Vector3 new_camera_forward = Vector3Normalize(desired_camera.target - desired_camera.position);
        const float angle_between_targets = Vector3Angle(old_camera_forward, new_camera_forward);
        if (angle_between_targets > EPSILON)
        {
            const Quaternion old_camera_rotation = QuaternionFromVector3ToVector3({1, 0, 0}, old_camera_forward);
            const Quaternion new_camera_rotation = QuaternionFromVector3ToVector3({1, 0, 0}, new_camera_forward);
            const float lerp_coefficient = std::min(angle_between_targets / (MAX_CAMERA_ANGULAR_SPEED * dt), 1.f);
            const Quaternion tmp_camera_rotation = QuaternionSlerp(old_camera_rotation, new_camera_rotation, lerp_coefficient);
            camera->camera.target = camera->camera.position + Vector3RotateByQuaternion({1, 0, 0}, tmp_camera_rotation);
        }
    }
    // FOVY
    {
        const float fovy_diff = desired_camera.fovy - camera->camera.fovy;
        const float fovy_change = std::min(MAX_CAMERA_FOVY_CHANGE * dt, abs(fovy_diff)) * (fovy_diff > 0.f ? 1.f : -1.f);
        camera->camera.fovy += fovy_change;
    }
    camera->camera.up = desired_camera.up;
    camera->camera.projection = desired_camera.projection;
}

namespace
{
    static constexpr float JUMP_SPEED = 10.f;

    static constexpr float GLOBAL_ANIMATION_SPEED = 60.f;

    static const otb::InternedString WAKING_UP_ANIMATION("WakingUp");
    static const otb::InternedString IDLE_ANIMATION("Idle");
    static const otb::InternedString JUMP_ANIMATION("Jump");
    static constexpr float JUMP_ANIMATION_DELAY = 25 / 60.f;
    static const otb::InternedString FLYING_ANIMATION("Flying");
    static const otb::InternedString WALKING_ANIMATION("WalkingCycle");
    static constexpr float WALKING_SPEED = 3.36408f;
    static constexpr float WALKING_ANIM_EPS = 0.7f;

    struct StateUpdateContext
    {
        otb::World* world;
        CharacterComponent* character_component;
        const InputReceiverComponent* input_receiver_component;
        otb::ModelComponent* model_component;
        otb::TransformComponent* transform_component;
        otb::VelocityComponent* velocity_component;
    };

    void update_state_WAKING_UP(StateUpdateContext& ctx)
    {
        using namespace otb;
        if (ctx.model_component->get_playing_animation() == InternedString::get_empty())
        {
            ctx.model_component->request_animation(WAKING_UP_ANIMATION, false);
            ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
        }
        else if (ctx.model_component->get_playing_animation() == WAKING_UP_ANIMATION)
        {
            ctx.model_component->request_animation(IDLE_ANIMATION, true);
        }
        else if (ctx.model_component->get_playing_animation() == IDLE_ANIMATION)
        {
            ctx.character_component->movement_state = CharacterComponent::MovementState::GROUNDED;
        }
    }

    void update_state_GROUNDED(StateUpdateContext& ctx)
    {
        if (ctx.input_receiver_component->extra_actions.contains(InputReceiverComponent::ActionNames::jump))
        {
            ctx.character_component->movement_state = CharacterComponent::MovementState::PREPARING_JUMP;
            ctx.character_component->extra_jump_delay = JUMP_ANIMATION_DELAY;
            ctx.model_component->request_animation(FLYING_ANIMATION, true);
            ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
        }
        else
        {
            const Vector3 character_forward_vector = Vector3RotateByQuaternion({1, 0, 0}, ctx.transform_component->transform.rotation);
            const float forward_projected_speed = Vector3DotProduct(character_forward_vector, ctx.velocity_component->velocity);
            if (abs(forward_projected_speed) < WALKING_ANIM_EPS)
            {
                ctx.model_component->request_animation(IDLE_ANIMATION, true);
                ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
            }
            else
            {
                ctx.model_component->request_animation(WALKING_ANIMATION, true);
                ctx.model_component->set_animation_speed(forward_projected_speed * GLOBAL_ANIMATION_SPEED / WALKING_SPEED);
            }
        }
    }

    void update_state_PREPARING_JUMP(StateUpdateContext& ctx)
    {
        if (ctx.model_component->get_playing_animation() == JUMP_ANIMATION)
        {
            if (ctx.character_component->extra_jump_delay > 0)
            {
                ctx.character_component->extra_jump_delay -= ctx.world->fixed_frame_time;
            }
            else
            {
                ctx.character_component->movement_state = CharacterComponent::MovementState::FLYING;
                ctx.character_component->extra_jump_delay = -1;
                ctx.velocity_component->velocity.y = JUMP_SPEED;
            }
        }
    }

    void update_state_FLYING(StateUpdateContext& ctx)
    {
        if (ctx.velocity_component->velocity.y == 0)
        {
            ctx.character_component->movement_state = CharacterComponent::MovementState::LANDING;
            ctx.model_component->request_animation(IDLE_ANIMATION, true);
        }
    }

    void update_state_LANDING(StateUpdateContext& ctx)
    {
        if (ctx.model_component->get_playing_animation() == IDLE_ANIMATION)
        {
            ctx.character_component->movement_state = CharacterComponent::MovementState::GROUNDED;
        }
    }
}

void CharacterSystem::update_state(otb::World* world)
{
    using namespace otb;


    for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
    {
        StateUpdateContext ctx {
            .world = world,
            
            .character_component = &*it,
            .input_receiver_component = it->entity->get_component<InputReceiverComponent>(),
            .model_component = it->entity->get_component<otb::ModelComponent>(),
            .transform_component = it->entity->get_component<TransformComponent>(),
            .velocity_component = it->entity->get_component<otb::VelocityComponent>(),
        };
        switch(it->movement_state)
        {
            case CharacterComponent::MovementState::WAKING_UP: update_state_WAKING_UP(ctx); break;
            case CharacterComponent::MovementState::GROUNDED: update_state_GROUNDED(ctx); break;
            case CharacterComponent::MovementState::PREPARING_JUMP: update_state_PREPARING_JUMP(ctx); break;
            case CharacterComponent::MovementState::FLYING: update_state_FLYING(ctx); break;
            case CharacterComponent::MovementState::LANDING: update_state_LANDING(ctx); break;
            default: OTB_ASSERT(false); break;
        }
    }
}
}