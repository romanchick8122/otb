#include "input_system.h"

#include "core/ecs/world.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"

#include "raylib.h"
#include "raymath.h"

namespace game
{
void InputSystem::collect_input_kb_mouse(otb::World* world)
{
    using namespace otb;

    Vector2 movement_request{0, 0};
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
        movement_request.y += 1;
    }
    if (IsKeyDown(KEY_A))
    {
        movement_request.y -= 1;
    }

    movement_request = Vector2Normalize(movement_request);

    const Vector2 mouse_delta = GetMouseDelta();
    static constexpr float mouse_sensitivity = -0.005f;

    std::unordered_set<InternedString> extra_actions;
    if (IsKeyDown(KEY_SPACE))
    {
        extra_actions.insert(InputReceiverComponent::ActionNames::jump);
    }

    for(auto it = world->components_begin<InputReceiverComponent>(); it != world->components_end<InputReceiverComponent>(); ++it)
    {
        it->analog_input = movement_request;
        it->rotation_input = mouse_sensitivity * mouse_delta.x;
        it->extra_actions = extra_actions;
    }
}

void InputSystem::apply_input(otb::World* world)
{
    using namespace otb;

    static constexpr float movement_speed = 10.f;
    static constexpr float jump_power = 10.f;

    for(auto it = world->components_begin<InputReceiverComponent>(); it != world->components_end<InputReceiverComponent>(); ++it)
    {
        CharacterComponent* character_component = it->entity->get_component<CharacterComponent>();
        if (character_component == nullptr)
            continue;

        auto* velocity_component = it->entity->get_component<VelocityComponent>();
        if (velocity_component == nullptr)
        {
            velocity_component = new VelocityComponent();
            velocity_component->apply_gravity = true;
            it->entity->add_component(velocity_component);
        }
        auto* transform_component = it->entity->get_component<TransformComponent>();

        const Vector3 oriented_move_vector = Vector3RotateByQuaternion({it->analog_input.x, 0, it->analog_input.y}, transform_component->transform.rotation);
        velocity_component->velocity += Vector3Scale(oriented_move_vector, world->fixed_frame_time * movement_speed);
        
        const Quaternion added_rotation = QuaternionFromAxisAngle({0, 1, 0}, it->rotation_input);
        transform_component->transform.rotation = QuaternionMultiply(transform_component->transform.rotation, added_rotation);

        if (it->extra_actions.contains(InputReceiverComponent::ActionNames::jump) && velocity_component->velocity.y == 0)
        {
            velocity_component->velocity += Vector3RotateByQuaternion({0, jump_power, 0}, transform_component->transform.rotation);
        }
    }
}
}