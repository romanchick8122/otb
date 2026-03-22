#include "item_pickup_component.h"

namespace game
{
ItemPickupComponent::ItemPickupComponent(otb::InternedString _item)
    : item(_item)
{
}

otb::ValueStorage ItemPickupComponent::serialize() const
{
    return std::string(item.c_str());
}

otb::Component* ItemPickupComponent::deserialize(const otb::ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    return new ItemPickupComponent(otb::InternedString(std::get<std::string>(vs.storage).c_str()));
}
}