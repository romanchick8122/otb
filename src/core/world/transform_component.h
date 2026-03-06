#pragma once

#include "core/ecs/component.h"

#include "raylib.h"

namespace otb
{
class TransformComponent : public Component
{
  public:
    ValueStorage serialize() const override;
    static Component* deserialize(const ValueStorage&);

    ~TransformComponent() override = default;

    Transform transform;
};
}