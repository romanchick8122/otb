#pragma once

#include "core/ecs/component.h"

#include "raylib.h"

namespace otb
{
class CameraComponent : public Component
{
  public:
    CameraComponent();

    ValueStorage serialize() const override;
    static Component* deserialize(const ValueStorage&);

    ~CameraComponent() override = default;

    Camera camera { 0 };
};
}