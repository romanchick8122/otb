#pragma once

#include "core/ecs/component.h"

namespace game
{
class CharacterComponent : public otb::Component
{
  public:
    otb::ValueStorage serialize() const override;
    static Component* deserialize(const otb::ValueStorage&);

    ~CharacterComponent() override = default;

    float camera_follow_distance = 0.f;
    float camera_follow_offset = 0.f;
};
}