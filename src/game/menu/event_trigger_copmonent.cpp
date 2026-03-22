#include "event_trigger_component.h"

namespace game
{
EventTriggerComponent::EventTriggerComponent(otb::InternedString v)
    : inside_event(v)
{
}

otb::ValueStorage EventTriggerComponent::serialize() const
{
    return std::string(inside_event.c_str());
}

otb::Component* EventTriggerComponent::deserialize(const otb::ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    return new EventTriggerComponent(std::get<std::string>(vs.storage).c_str());
}
}