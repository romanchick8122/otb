#pragma once

#include "core/ecs/component.h"

#include <vector>

namespace game
{
class UpstreamInteractionComponent : public otb::Component
{
  public:
    ~UpstreamInteractionComponent() override = default;

    std::vector<otb::InternedString> events;
};
}