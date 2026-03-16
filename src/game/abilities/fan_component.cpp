#include "fan_component.h"

#include "core/asset/value_storage_utils.h"

namespace game
{
otb::ValueStorage FanComponent::serialize() const
{
    return otb::ValueStorageUtils::serialize(power);
}

otb::Component* FanComponent::deserialize(const otb::ValueStorage& vs)
{
    auto* result = new FanComponent();
    result->power = otb::ValueStorageUtils::deserialize<float>(vs);
    return result;
}
}