#pragma once

#include "core/ecs/component.h"

#include "raylib.h"

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
    bool is_on_surface = false;
  private:
};
}