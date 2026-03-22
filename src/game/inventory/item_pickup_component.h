#pragma once

#include "core/ecs/component.h"

namespace game
{
class ItemPickupComponent : public otb::Component
{
  public:
    ItemPickupComponent(otb::InternedString);

    otb::ValueStorage serialize() const override;
    static otb::Component* deserialize(const otb::ValueStorage&);

    ~ItemPickupComponent() override = default;

    otb::InternedString item;

    bool pickup_active = true;
};
}