#pragma once

#include "core/ecs/component.h"

namespace game
{
class EventTriggerComponent : public otb::Component
{
  public:
    EventTriggerComponent(otb::InternedString);

    otb::ValueStorage serialize() const override;
    static otb::Component* deserialize(const otb::ValueStorage&);

    ~EventTriggerComponent() override = default;

    otb::InternedString inside_event;
};
}