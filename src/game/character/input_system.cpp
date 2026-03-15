#include "input_system.h"

#include "core/ecs/world.h"
#include "core/render/model_component.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"

#include "raylib.h"
#include "raymath.h"

#include <array>

namespace game
{
void InputSystem::clear_input(otb::World* world)
{
    for (auto it = world->components_begin<InputReceiverComponent>(); it != world->components_end<InputReceiverComponent>(); ++it)
    {
        it->extra_actions.clear();
    }
}
void InputSystem::collect_input_kb_mouse(otb::World* world)
{
    using namespace otb;

    Vector2 movement_request{0, 0};
    float rotation_input = 0;
    if (IsKeyDown(KEY_W))
    {
        movement_request.x += 1;
    }
    if (IsKeyDown(KEY_S))
    {
        movement_request.x -= 1;
    }
    if (IsKeyDown(KEY_D))
    {
        movement_request.y -= 1;
    }
    if (IsKeyDown(KEY_A))
    {
        movement_request.y += 1;
    }

    const Vector2 mouse_delta = GetMouseDelta();
    static constexpr float mouse_sensitivity = 1.f;
    const Vector2 analog_input = mouse_delta * mouse_sensitivity;

    std::vector<std::pair<InternedString, float>> actions;
    if (IsKeyDown(KEY_SPACE))
    {
        actions.emplace_back(InputReceiverComponent::ActionNames::jump, 0.0f);
    }
    if (IsKeyDown(KEY_ONE))
    {
        actions.emplace_back(InputReceiverComponent::ActionNames::ability_1, 0.f);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        actions.emplace_back(InputReceiverComponent::ActionNames::aim, 0.f);
    }

    for(auto it = world->components_begin<InputReceiverComponent>(); it != world->components_end<InputReceiverComponent>(); ++it)
    {
        it->analog_input = movement_request;
        it->secondary_analog_input = analog_input;
        for (const auto& [k, v] : actions)
        {
            it->action_queue.request(k, v);
        }
    }
}

void InputSystem::update_action_queue(otb::World* world)
{
    for (auto it = world->components_begin<InputReceiverComponent>(); it != world->components_end<InputReceiverComponent>(); ++it)
    {
        auto& delays = it->action_queue.delays;
        float remaining_time = world->fixed_frame_time;
        while (!delays.empty() && remaining_time > 0 && delays.front().second < remaining_time)
        {
            it->extra_actions.insert(delays.front().first);
            remaining_time -= delays.front().second;
            delays.erase(delays.begin());
        }
        if (!delays.empty())
        {
            delays.front().second -= remaining_time;
        }
    }
}

void InputSystem::apply_input(otb::World* world)
{
    using namespace otb;

    static constexpr float MOVEMENT_SPEED = 10.f;
    static constexpr float ROTATION_SPEED = 3.f;
    
    static std::array<bool, std::to_underlying(CharacterComponent::MovementState::COUNT)> apply_movement;
    static std::array<bool, std::to_underlying(CharacterComponent::MovementState::COUNT)> apply_rotation;

    apply_movement[std::to_underlying(CharacterComponent::MovementState::GROUNDED)] = true;
    apply_movement[std::to_underlying(CharacterComponent::MovementState::FLYING)] = true;

    apply_rotation[std::to_underlying(CharacterComponent::MovementState::GROUNDED)] = true;
    apply_rotation[std::to_underlying(CharacterComponent::MovementState::PREPARING_JUMP)] = true;
    apply_rotation[std::to_underlying(CharacterComponent::MovementState::FLYING)] = true;


    for(auto it = world->components_begin<InputReceiverComponent>(); it != world->components_end<InputReceiverComponent>(); ++it)
    {
        CharacterComponent* character_component = it->entity->get_component<CharacterComponent>();
        if (character_component == nullptr)
            continue;
        auto* velocity_component = it->entity->get_component<VelocityComponent>();
        if (velocity_component == nullptr) [[unlikely]]
        {
            velocity_component = new VelocityComponent();
            velocity_component->apply_gravity = true;
            it->entity->add_component(velocity_component);
        }

        auto* transform_component = it->entity->get_component<TransformComponent>();

        if (apply_movement[std::to_underlying(character_component->movement_state)])
        {
            const Vector3 oriented_move_vector = Vector3RotateByQuaternion(
                {it->analog_input.x, 0, 0},
                transform_component->transform.rotation
            );
            velocity_component->velocity += Vector3Scale(oriented_move_vector, MOVEMENT_SPEED);
        }
        if (apply_rotation[std::to_underlying(character_component->movement_state)])
        {
            const Quaternion added_rotation = QuaternionFromAxisAngle(
                {0, 1, 0},
                it->analog_input.y * ROTATION_SPEED * world->fixed_frame_time
            );
            transform_component->transform.rotation = QuaternionMultiply(transform_component->transform.rotation, added_rotation);
        }
    }
}
}