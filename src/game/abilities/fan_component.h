#pragma once

#include "core/ecs/component.h"

namespace game
{
class FanComponent : public otb::Component
{
  public:
    otb::ValueStorage serialize() const override;
    static otb::Component* deserialize(const otb::ValueStorage&);

    ~FanComponent() = default;

    float power = 1.f;
};
}