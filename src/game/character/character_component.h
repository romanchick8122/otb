#pragma once

#include "core/ecs/component.h"

#include <raylib.h>

namespace game
{
class BoxComponent;
class SurfaceComponent;

class CharacterComponent : public otb::Component
{
  public:
    otb::ValueStorage serialize() const override;
    static Component* deserialize(const otb::ValueStorage&);

    ~CharacterComponent() override = default;

    // Serializable
    float camera_follow_distance = 0.f;
    float camera_follow_offset = 0.f;
    Vector3 get_camera_forward() const;
    

    // Runtime
    float pitch = 0.f;
    float yaw = 0.f;

    enum class MovementState : uint8_t 
    {
        WAKING_UP,
        GROUNDED,
        PREPARING_JUMP,
        FLYING,
        LANDING,
        AIMING,
        PULLING,
        PREPARE_PUSHING,
        PUSHING,
        STOP_PUSHING,

        UMBRELLA_GROUNDED,
        UMBRELLA_FLYING,

        COUNT,
    } movement_state = MovementState::WAKING_UP;

    struct StateDataAIMING 
    {
        Vector2 aim_direction;
    };
    struct StateDataPUSHING 
    {
        Vector3 pushing_direction;
        bool high_push = false;
    };
    struct StateDataGrounded 
    {
        float time_in_idle = 0;
    };
    std::variant<
        std::monostate,
        StateDataAIMING,
        StateDataPUSHING,
        StateDataGrounded
    > state_data;

    const BoxComponent* pushing_obj = nullptr;
    Vector3 pushing_direction;
    
    float movement_speed_multiplier = 1.f;
};
}