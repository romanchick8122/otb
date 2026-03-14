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

void InputReceiverComponent::ActionQueue::request(otb::InternedString action, float delay)
{
    float total_prev_delay = 0;
    size_t i = 0;
    for (; i < delays.size() && delay > total_prev_delay; total_prev_delay += delays[i].second, ++i) {}
    const float inserted_delay = delay - total_prev_delay;
    delays.insert(delays.begin() + i, {action, inserted_delay});
    if (i + 1 < delays.size())
    {
        delays[i + 1].second -= inserted_delay;
    }
}
}