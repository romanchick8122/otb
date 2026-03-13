#include "transform_component.h"

#include "core/asset/value_storage_utils.h"

#include "raymath.h"


namespace otb
{
ValueStorage TransformComponent::serialize() const
{
    return ValueStorageUtils::serialize(transform);
}

Component* TransformComponent::deserialize(const ValueStorage& vs)
{
    auto* result = new TransformComponent();
    result->transform = ValueStorageUtils::deserialize<Transform>(vs);
    return result;
}
}