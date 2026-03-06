#pragma once

#include "core/ecs/component.h"

#include "raylib.h"

#include <functional>

namespace otb
{
class CollisionComponent : public Component
{
  public:
    using CollisionTestFn = std::function<RayCollision(const Ray&)>;
    using CallbackFn = std::function<void(Vector3)>;

    CollisionComponent(const CollisionTestFn&, const CallbackFn&);

    ~CollisionComponent() = default;

  private:
    CollisionTestFn test_fn;
    CallbackFn callback_fn;
    friend class PhysicsSystem;
};
}