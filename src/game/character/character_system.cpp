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
void CharacterSystem::character_follow_camera(otb::World* world, float)
{
    using namespace otb;

    CharacterComponent* character = nullptr;
    for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
    {
        OTB_ASSERT(character == nullptr);
        character = &*it;
    }

    const Transform& character_transform = character->entity->get_component<TransformComponent>()->transform;

    CameraComponent* camera = world->get_world_entity()->get_component<otb::CameraComponent>();

    Vector3 desired_position =
        character_transform.translation +
        Vector3RotateByQuaternion({-1, 0, 0}, character_transform.rotation) * character->camera_follow_distance +
        Vector3{0, character->camera_follow_offset, 0};
    
    camera->camera.position = (camera->camera.position + desired_position) / 2.f;
    camera->camera.target = character_transform.translation;
}

void CharacterSystem::update_state(otb::World* world)
{
    using namespace otb;

    static constexpr float JUMP_SPEED = 10.f;

    static constexpr float GLOBAL_ANIMATION_SPEED = 60.f;

    static const InternedString WAKING_UP_ANIMATION("WakingUp");
    static const InternedString IDLE_ANIMATION("Idle");
    static const InternedString JUMP_ANIMATION("Jump");
    static constexpr float JUMP_ANIMATION_DELAY = 25 / 60.f;
    static const InternedString FLYING_ANIMATION("Flying");
    static const InternedString WALKING_ANIMATION("WalkingCycle");
    static constexpr float WALKING_SPEED = 3.36408f;
    static constexpr float WALKING_ANIM_EPS = 0.7f;

    for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
    {
        auto* model_component = it->entity->get_component<otb::ModelComponent>();
        auto* velocity_component = it->entity->get_component<otb::VelocityComponent>();
        const auto* input_receiver_component = it->entity->get_component<InputReceiverComponent>();
        const auto* transform_component = it->entity->get_component<TransformComponent>();

        if (model_component->get_playing_animation() == InternedString::get_empty()) [[unlikely]]
        {
            model_component->request_animation(WAKING_UP_ANIMATION, false);
            model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
        }
        else if (model_component->get_playing_animation() == WAKING_UP_ANIMATION) [[unlikely]]
        {
            model_component->request_animation(IDLE_ANIMATION, true);
        }

        switch (it->movement_state)
        {
            case CharacterComponent::MovementState::GROUNDED:
            {
                if (input_receiver_component->extra_actions.contains(InputReceiverComponent::ActionNames::jump))
                {
                    it->movement_state = CharacterComponent::MovementState::PREPARING_JUMP;
                    it->extra_jump_delay = JUMP_ANIMATION_DELAY;
                    model_component->request_animation(FLYING_ANIMATION, true);
                    model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
                }
                else
                {
                    const Vector3 character_forward_vector = Vector3RotateByQuaternion({1, 0, 0}, transform_component->transform.rotation);
                    const float forward_projected_speed = Vector3DotProduct(character_forward_vector, velocity_component->velocity);
                    if (abs(forward_projected_speed) < WALKING_ANIM_EPS)
                    {
                        model_component->request_animation(IDLE_ANIMATION, true);
                        model_component->set_animation_speed(GLOBAL_ANIMATION_SPEED);
                    }
                    else
                    {
                        model_component->request_animation(WALKING_ANIMATION, true);
                        model_component->set_animation_speed(forward_projected_speed * GLOBAL_ANIMATION_SPEED / WALKING_SPEED);
                    }
                }
                break;
            }
            case CharacterComponent::MovementState::PREPARING_JUMP:
            {
                if (it->extra_jump_delay > 0) {
                }
                if (model_component->get_playing_animation() == JUMP_ANIMATION)
                {
                    if (it->extra_jump_delay > 0)
                    {
                        it->extra_jump_delay -= world->fixed_frame_time;
                    }
                    else
                    {
                        it->movement_state = CharacterComponent::MovementState::FLYING;
                        it->extra_jump_delay = -1;
                        velocity_component->velocity.y = JUMP_SPEED;
                    }
                }
                break;
            }
            case CharacterComponent::MovementState::FLYING:
            {
                if (velocity_component->velocity.y == 0)
                {
                    it->movement_state = CharacterComponent::MovementState::GROUNDED;
                    model_component->request_animation(IDLE_ANIMATION, true);
                }
                break;
            }
        }
    }
}
}