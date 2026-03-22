#pragma once

#include "core/ecs/component.h"
#include "core/interned_string.h"

#include <unordered_set>

namespace game
{
class InventoryComponent : public otb::Component
{
  public:
    ~InventoryComponent() override = default;

    std::unordered_set<otb::InternedString> items;
    otb::InternedString active_item = otb::InternedString("thread_n_needle");
};
}