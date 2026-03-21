#include "character_system.h"

#include "core/ecs/world.h"
#include "core/render/camera_component.h"
#include "core/render/model_component.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/abilities/box_attachment_ability_component.h"
#include "game/box/box_component.h"
#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"

#include <raymath.h>

#include <iostream>

namespace game
{
void CharacterSystem::update_camera(otb::World* world, float dt)
{
    using namespace otb;

    static constexpr auto get_camera_behind_back = [](const CharacterComponent* character)
    {
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
    };
    static constexpr auto get_first_person_camera = [](const CharacterComponent* character)
    {
        OTB_ASSERT(std::holds_alternative<CharacterComponent::StateDataAIMING>(character->state_data));
        const auto& state_data = std::get<CharacterComponent::StateDataAIMING>(character->state_data);
        const Transform& character_transform = character->entity->get_component<TransformComponent>()->transform;
        const Vector3 character_forward = Vector3RotateByQuaternion({1, 0, 0}, character_transform.rotation);
        const Vector3 camera_forward = Vector3RotateByQuaternion(Vector3RotateByQuaternion({1, 0, 0}, QuaternionFromEuler(0, state_data.aim_direction.x, state_data.aim_direction.y)), character_transform.rotation);
        const Vector3 desired_position = character_transform.translation + character_forward * character_transform.scale.x * 0.5f;
        return Camera3D {
            .position = desired_position,
            .target = desired_position + camera_forward,
            .up = {0, 1, 0},
            .fovy = 90,
            .projection = CAMERA_PERSPECTIVE,
        };
    };

    const Camera3D desired_camera = [world]
    {
        CharacterComponent* character = nullptr;
        for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
        {
            OTB_ASSERT(character == nullptr);
            character = &*it;
        }

        if (character->movement_state == CharacterComponent::MovementState::AIMING)
        {
            return get_first_person_camera(character);
        }
        else
        {
            return get_camera_behind_back(character);
        }
    }();

    CameraComponent* camera = world->get_world_entity()->get_component<otb::CameraComponent>();

    static constexpr float MAX_CAMERA_SPEED = 50.f;                 // m/s
    static constexpr float MAX_CAMERA_ANGULAR_SPEED = .5f;          // rad/s
    static constexpr float MAX_CAMERA_FOVY_CHANGE = 30.f;           // deg/s

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
            const float lerp_coefficient = std::min(angle_between_targets / MAX_CAMERA_ANGULAR_SPEED / dt, 1.f);
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
    static constexpr float JUMP_SPEED = 17.6f;

    static constexpr float GLOBAL_ANIMATION_SPEED = 60.f;

    static const otb::InternedString WAKING_UP_ANIMATION("WakingUp");
    static const otb::InternedString IDLE_ANIMATION("Idle");
    static const otb::InternedString JUMP_ANIMATION("Jump");
    static const otb::InternedString FLYING_ANIMATION("Flying");
    static const otb::InternedString WALKING_ANIMATION("WalkingCycle");
    static const otb::InternedString THROW_ANIMATION("Throw");
    static const otb::InternedString PULL_ANIMATION("PullCycle");
    static constexpr float WALKING_SPEED = 3.36408f;
    static constexpr float PULL_SPEED = -3.1307f;
    static constexpr float WALKING_ANIM_EPS = 0.7f;

    static constexpr Vector2 AIM_LIMIT_MIN { -1.f, -0.5f };
    static constexpr Vector2 AIM_LIMIT_MAX { 1.f, 1.f };

    struct StateUpdateContext
    {
        otb::World* world;
        CharacterComponent* character_component;
        const InputReceiverComponent* input_receiver_component;
        otb::ModelComponent* model_component;
        otb::TransformComponent* transform_component;
        otb::VelocityComponent* velocity_component;
        BoxComponent* box_component;
    };

    void set_state(StateUpdateContext& ctx, CharacterComponent::MovementState new_state)
    {
        ctx.character_component->movement_state = new_state;
        switch (ctx.character_component->movement_state) {
            case CharacterComponent::MovementState::AIMING:
                ctx.character_component->state_data = CharacterComponent::StateDataAIMING{};
                break;
            default:
                ctx.character_component->state_data = std::monostate{};
                break;
        }
    }

    void select_animation_from_movement_speed(
        StateUpdateContext& ctx,
        float forward_eps,
        float backward_eps,
        otb::InternedString anim_forward,
        float forward_speed_scale,
        otb::InternedString anim_neutral,
        otb::InternedString anim_backward,
        float backward_speed_scale
    )
    {
        const Vector3 character_forward_vector = Vector3RotateByQuaternion({1, 0, 0}, ctx.transform_component->transform.rotation);
        const float forward_projected_speed = Vector3DotProduct(character_forward_vector, ctx.velocity_component->velocity);
        if (forward_projected_speed > forward_eps)
        {
            ctx.model_component->request_animation(anim_forward, true);
            ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED * (forward_speed_scale == 0 ? 1 : forward_projected_speed * forward_speed_scale));
            return;
        }
        if (forward_projected_speed < -backward_eps)
        {
            ctx.model_component->request_animation(anim_backward, true);
            ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED * (backward_speed_scale == 0 ? 1 : forward_projected_speed * backward_speed_scale));
            return;
        }
        ctx.model_component->request_animation(anim_neutral, true);
        ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
    }

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
            set_state(ctx, CharacterComponent::MovementState::GROUNDED);
        }
    }

    void update_state_GROUNDED(StateUpdateContext& ctx)
    {
        if (ctx.box_component->rests_on == nullptr)
        {
            set_state(ctx, CharacterComponent::MovementState::FLYING);
            ctx.model_component->request_animation(FLYING_ANIMATION, true);
            ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
        }
        else if (ctx.input_receiver_component->extra_actions.contains(InputReceiverComponent::ActionNames::jump))
        {
            set_state(ctx, CharacterComponent::MovementState::PREPARING_JUMP);
            ctx.model_component->request_animation(JUMP_ANIMATION, true);
            ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
        }
        else if (ctx.input_receiver_component->extra_actions.contains(InputReceiverComponent::ActionNames::aim))
        {
            set_state(ctx, CharacterComponent::MovementState::AIMING);
        }
        else
        {
            select_animation_from_movement_speed(ctx, WALKING_ANIM_EPS, WALKING_ANIM_EPS, WALKING_ANIMATION, 1 / WALKING_SPEED, IDLE_ANIMATION, WALKING_ANIMATION, 1 / WALKING_SPEED);
        }
    }

    void update_state_PREPARING_JUMP(StateUpdateContext& ctx)
    {
        if (ctx.model_component->get_playing_animation() == JUMP_ANIMATION)
        {
            set_state(ctx, CharacterComponent::MovementState::FLYING);
            ctx.model_component->request_animation(FLYING_ANIMATION, true);
            ctx.velocity_component->velocity.y = JUMP_SPEED;
        }
    }

    void update_state_FLYING(StateUpdateContext& ctx)
    {
        if (ctx.velocity_component->velocity.y == 0)
        {
            set_state(ctx, CharacterComponent::MovementState::LANDING);
            ctx.model_component->request_animation(IDLE_ANIMATION, true);
        }
    }

    void update_state_LANDING(StateUpdateContext& ctx)
    {
        if (ctx.model_component->get_playing_animation() == IDLE_ANIMATION)
        {
            set_state(ctx, CharacterComponent::MovementState::GROUNDED);
        }
    }

    void update_state_AIMING(StateUpdateContext& ctx)
    {
        if (!ctx.input_receiver_component->extra_actions.contains(InputReceiverComponent::ActionNames::aim))
        {
            if (ctx.character_component->entity->get_component<BoxAttachmentAbilityComponent>()->attached_box != nullptr)
            {
                set_state(ctx, CharacterComponent::MovementState::PULLING);
            }
            else
            {
                set_state(ctx, CharacterComponent::MovementState::GROUNDED);
            }
            return;
        }
        OTB_ASSERT(std::holds_alternative<CharacterComponent::StateDataAIMING>(ctx.character_component->state_data));
        auto& state_data = std::get<CharacterComponent::StateDataAIMING>(ctx.character_component->state_data);

        std::cerr << state_data.aim_direction.x << " " << state_data.aim_direction.y << "\n";
        state_data.aim_direction -= ctx.input_receiver_component->secondary_analog_input * ctx.world->fixed_frame_time;
        state_data.aim_direction = Vector2Clamp(state_data.aim_direction, AIM_LIMIT_MIN, AIM_LIMIT_MAX);

        if (ctx.character_component->entity->get_component<BoxAttachmentAbilityComponent>()->attached_box != nullptr)
        {
            ctx.model_component->request_animation(THROW_ANIMATION, true);
        }
    }

    void update_state_PULLING(StateUpdateContext& ctx)
    {
        using namespace otb;
        const BoxAttachmentAbilityComponent* ability = ctx.character_component->entity->get_component<BoxAttachmentAbilityComponent>();
        const auto attached_box = ability->attached_box;
        if (attached_box == nullptr)
        {
            set_state(ctx, CharacterComponent::MovementState::GROUNDED);
            return;
        }
        Vector3 to_box = attached_box->entity->get_component<TransformComponent>()->transform.translation - ctx.transform_component->transform.translation;
        to_box.y = 0;
        ctx.transform_component->transform.rotation = QuaternionFromVector3ToVector3({1, 0, 0}, Vector3Normalize(to_box));
        select_animation_from_movement_speed(ctx, WALKING_ANIM_EPS, WALKING_ANIM_EPS, WALKING_ANIMATION, 1 / WALKING_SPEED, IDLE_ANIMATION, PULL_ANIMATION, 1 / PULL_SPEED);
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
            .box_component = it->entity->get_component<BoxComponent>(),
        };
        switch(it->movement_state)
        {
            case CharacterComponent::MovementState::WAKING_UP: update_state_WAKING_UP(ctx); break;
            case CharacterComponent::MovementState::GROUNDED: update_state_GROUNDED(ctx); break;
            case CharacterComponent::MovementState::PREPARING_JUMP: update_state_PREPARING_JUMP(ctx); break;
            case CharacterComponent::MovementState::FLYING: update_state_FLYING(ctx); break;
            case CharacterComponent::MovementState::LANDING: update_state_LANDING(ctx); break;
            case CharacterComponent::MovementState::AIMING: update_state_AIMING(ctx); break;
            case CharacterComponent::MovementState::PULLING: update_state_PULLING(ctx); break;
            default: OTB_ASSERT(false); break;
        }
    }
}
}