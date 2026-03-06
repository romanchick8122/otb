#include "collision_component.h"

namespace otb
{
CollisionComponent::CollisionComponent(const CollisionTestFn& test, const CallbackFn& callback)
    : test_fn(test)
    , callback_fn(callback)
{
}
}