#include "input_receiver_component.h"

namespace game
{
otb::ValueStorage InputReceiverComponent::serialize() const
{
  return std::string{ "RUNTIME" };
}

otb::Component* InputReceiverComponent::deserialize(const otb::ValueStorage&)
{
  return new InputReceiverComponent();
}

const otb::InternedString InputReceiverComponent::ActionNames::jump("jump");
const otb::InternedString InputReceiverComponent::ActionNames::ability_1("ability_1");
}