#include "character_system.h"

#include "core/ecs/world.h"
#include "core/math/math_utils.h"
#include "core/render/camera_component.h"
#include "core/render/model_component.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/abilities/box_attachment_ability_component.h"
#include "game/box/box_component.h"
#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"
#include "game/inventory/inventory_component.h"

#include <raymath.h>

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
    static const otb::InternedString LANDING_ON_PLACE_ANIMATION("LandingOnPlace");
    static const otb::InternedString LANDING_ON_MOVE_ANIMATION("LandingOnMove");
    static const otb::InternedString WALKING_ANIMATION("WalkingCycle");
    static const otb::InternedString THROW_ANIMATION("Throw");
    static const otb::InternedString PULL_ANIMATION("PullCycle");
    static const otb::InternedString LOW_PUSH_ANIMATION("LowPushingCycle");
    static const otb::InternedString HIGH_PUSH_ANIMATION("HighPushingCycle");
    static constexpr float WALKING_SPEED = 3.36408f;
    static constexpr float PULL_SPEED = -3.1307f;
    static constexpr float HIGH_PUSHING_SPEED = 1.10695f;
    static constexpr float LOW_PUSHING_SPEED = 1.97993f;
    static constexpr float WALKING_ANIM_EPS = 0.7f;
    static constexpr float HIGHT_FOR_HIGH_PUSH = 2.75f;
    static constexpr float SPEED_FOR_NOT_SLIDING = 0.0f;

    static constexpr Vector2 AIM_LIMIT_MIN { -1.f, -0.5f };
    static constexpr Vector2 AIM_LIMIT_MAX { 1.f, 1.f };

    static constexpr float PUSHING_MOVEMENT_SPEED_MULTIPLIER = 0.65f;
    static constexpr float PULLING_MOVEMENT_SPEED_MULTIPLIER = 0.65f;

    static constexpr float ROTATION_SLERP_FACTOR = 5.f;

    static constexpr float PUSHING_MAX_OVERHANG_SIZE = 1.f;
    static constexpr float PUSHING_MAX_ANGLE_RAD = 45.f * DEG2RAD;

    static const otb::InternedString ABILITY_ITEM_THREAD_N_NEEDLE("thread_n_needle");

    struct StateUpdateContext
    {
        otb::World* world;
        BoxComponent* box_component;
        CharacterComponent* character_component;
        const InputReceiverComponent* input_receiver_component;
        const InventoryComponent* inventory_component;
        otb::ModelComponent* model_component;
        otb::TransformComponent* transform_component;
        otb::VelocityComponent* velocity_component;
    };

    void set_state(StateUpdateContext& ctx, CharacterComponent::MovementState new_state)
    {
        using namespace otb;
        ctx.character_component->movement_state = new_state;
        switch (ctx.character_component->movement_state) {
            case CharacterComponent::MovementState::AIMING:
                ctx.character_component->state_data = CharacterComponent::StateDataAIMING{};
                break;
            case CharacterComponent::MovementState::PREPARE_PUSHING:
                ctx.character_component->state_data = CharacterComponent::StateDataPUSHING {
                    .pushing_direction = ctx.character_component->pushing_direction,
                    .high_push = ctx.character_component->pushing_obj->entity->get_component<TransformComponent>()->transform.scale.y >= HIGHT_FOR_HIGH_PUSH,
                };
                break;
            case CharacterComponent::MovementState::PUSHING:
                OTB_ASSERT(std::holds_alternative<CharacterComponent::StateDataPUSHING>(ctx.character_component->state_data));
                break;
            default:
                ctx.character_component->state_data = std::monostate{};
                break;
        }

        // Movement speed
        if (ctx.character_component->movement_state == CharacterComponent::MovementState::PUSHING)
        {
            ctx.character_component->movement_speed_multiplier = PUSHING_MOVEMENT_SPEED_MULTIPLIER;
        }
        else if (ctx.character_component->movement_state == CharacterComponent::MovementState::PULLING)
        {
            ctx.character_component->movement_speed_multiplier = PULLING_MOVEMENT_SPEED_MULTIPLIER;
        }
        else
        {
            ctx.character_component->movement_speed_multiplier = 1.f;
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

    void set_desired_rotation(StateUpdateContext& ctx, Quaternion rotation)
    {
        float slerp_factor = ROTATION_SLERP_FACTOR * ctx.world->fixed_frame_time;
        ctx.transform_component->transform.rotation = QuaternionSlerp(ctx.transform_component->transform.rotation, rotation, slerp_factor);
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
        using namespace otb;
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
        else if (ctx.input_receiver_component->extra_actions.contains(InputReceiverComponent::ActionNames::aim) &&
                 ctx.inventory_component->active_item == ABILITY_ITEM_THREAD_N_NEEDLE)
        {
            set_state(ctx, CharacterComponent::MovementState::AIMING);
        } 
        else if ([&]{
            if (ctx.character_component->pushing_obj == nullptr)
            {
                return false;
            }

            {
                const Vector3 character_forward = Vector3RotateByQuaternion({1, 0, 0}, ctx.transform_component->transform.rotation);
                const float push_angle = abs(acos(Clamp(Vector3DotProduct(character_forward, ctx.character_component->pushing_direction), -1.f, 1.f)));
                if (push_angle > PUSHING_MAX_ANGLE_RAD)
                {
                    return false;
                }
            }
            {
                const Vector3 pushing_ort { -ctx.character_component->pushing_direction.z, ctx.character_component->pushing_direction.y, ctx.character_component->pushing_direction.x };
                const Transform& target_transform = ctx.character_component->pushing_obj->entity->get_component<TransformComponent>()->transform;
                const float box_edge_size = abs(Vector3DotProduct(target_transform.scale, pushing_ort));
                const float distance_to_edge_center = abs(Vector3DotProduct(target_transform.translation - ctx.transform_component->transform.translation, pushing_ort));
                const float character_edge_size = ctx.transform_component->transform.scale.z;
                const float overhang = distance_to_edge_center - (box_edge_size - character_edge_size) / 2.f;
                if (overhang > PUSHING_MAX_OVERHANG_SIZE)
                {
                    return false;
                }
            }
            return true;
        }())
        {
            set_state(ctx, CharacterComponent::MovementState::PREPARE_PUSHING);
            if (std::get<CharacterComponent::StateDataPUSHING>(ctx.character_component->state_data).high_push)
            ctx.model_component->request_animation(HIGH_PUSH_ANIMATION, true);
            else ctx.model_component->request_animation(LOW_PUSH_ANIMATION, true);
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
        if (ctx.box_component->rests_on != nullptr)
        {
            set_state(ctx, CharacterComponent::MovementState::LANDING);
            const Vector3 character_forward_vector = Vector3RotateByQuaternion({1, 0, 0}, ctx.transform_component->transform.rotation);
            const float forward_projected_speed = Vector3DotProduct(character_forward_vector, ctx.velocity_component->velocity);
            ctx.model_component->request_animation(FloatEquals(forward_projected_speed, SPEED_FOR_NOT_SLIDING) ? LANDING_ON_PLACE_ANIMATION : LANDING_ON_MOVE_ANIMATION, false);
        }
    }

    void update_state_LANDING(StateUpdateContext& ctx)
    {
        if (ctx.model_component->get_playing_animation() == LANDING_ON_MOVE_ANIMATION || ctx.model_component->get_playing_animation() == LANDING_ON_PLACE_ANIMATION)
        {
            ctx.model_component->request_animation(IDLE_ANIMATION, true);
            return;
        } 
        else if (ctx.model_component->get_playing_animation() == IDLE_ANIMATION)
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
        ctx.transform_component->transform.rotation = MathUtils::get_rotation_from_to({1, 0, 0}, Vector3Normalize(to_box));
        select_animation_from_movement_speed(ctx, WALKING_ANIM_EPS, WALKING_ANIM_EPS, WALKING_ANIMATION, 1 / WALKING_SPEED, IDLE_ANIMATION, PULL_ANIMATION, 1 / PULL_SPEED);
    }

    void update_state_PREPARE_PUSHING(StateUpdateContext& ctx)
    {
        set_desired_rotation(ctx, otb::MathUtils::get_rotation_from_to({1, 0, 0}, std::get<CharacterComponent::StateDataPUSHING>(ctx.character_component->state_data).pushing_direction));
        if (ctx.model_component->get_playing_animation() == HIGH_PUSH_ANIMATION || ctx.model_component->get_playing_animation() == LOW_PUSH_ANIMATION)
        {
            set_state(ctx, CharacterComponent::MovementState::PUSHING);
        }
    }

    void update_state_PUSHING(StateUpdateContext& ctx)
    {
        if(ctx.character_component->pushing_obj == nullptr)
        {
            set_state(ctx, CharacterComponent::MovementState::STOP_PUSHING);
            ctx.model_component->request_animation(IDLE_ANIMATION, true);
            ctx.model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
            return;
        } 
        if (std::get<CharacterComponent::StateDataPUSHING>(ctx.character_component->state_data).high_push)
        {
            select_animation_from_movement_speed(ctx, WALKING_ANIM_EPS, WALKING_ANIM_EPS, HIGH_PUSH_ANIMATION, 1 / HIGH_PUSHING_SPEED, IDLE_ANIMATION, WALKING_ANIMATION, 1 / WALKING_SPEED);    
        }
        else
        {
            select_animation_from_movement_speed(ctx, WALKING_ANIM_EPS, WALKING_ANIM_EPS, LOW_PUSH_ANIMATION, 1 / LOW_PUSHING_SPEED, IDLE_ANIMATION, WALKING_ANIMATION, 1 / WALKING_SPEED);
        }
        set_desired_rotation(ctx, otb::MathUtils::get_rotation_from_to({1, 0, 0}, ctx.character_component->pushing_direction));
    }

    void update_state_STOP_PUSHING(StateUpdateContext& ctx)
    {
        if (ctx.model_component->get_playing_animation() == IDLE_ANIMATION)
        {
            set_state(ctx, CharacterComponent::MovementState::GROUNDED);
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
            
            .box_component = it->entity->get_component<BoxComponent>(),
            .character_component = &*it,
            .input_receiver_component = it->entity->get_component<InputReceiverComponent>(),
            .inventory_component = it->entity->get_component<InventoryComponent>(),
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
            case CharacterComponent::MovementState::AIMING: update_state_AIMING(ctx); break;
            case CharacterComponent::MovementState::PULLING: update_state_PULLING(ctx); break;
            case CharacterComponent::MovementState::PREPARE_PUSHING: update_state_PREPARE_PUSHING(ctx); break;
            case CharacterComponent::MovementState::PUSHING: update_state_PUSHING(ctx); break;
            case CharacterComponent::MovementState::STOP_PUSHING: update_state_STOP_PUSHING(ctx); break;
            default: OTB_ASSERT(false); break;
        }
    }
}
}