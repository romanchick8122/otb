#pragma once

#include "core/ecs/component.h"

#include <raylib.h>

namespace game
{
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

    // Runtime
    enum class MovementState : uint8_t {
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
        COUNT,
    } movement_state = MovementState::WAKING_UP;

    struct StateDataAIMING {
        Vector2 aim_direction;
    };
    struct StateDataPREPARE_PUSHING {
        Vector3 pushing_direction;
    };
    std::variant<
        std::monostate,
        StateDataAIMING,
        StateDataPREPARE_PUSHING
    > state_data;

    bool is_pushing = false;
    Vector3 pushing_direction;

    float movement_speed_multiplier = 1.f;
};
}