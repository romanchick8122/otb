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

    std::vector<otb::InternedString> items;
    otb::InternedString active_item = otb::InternedString::get_empty();

    bool hud_open = true;
    size_t hud_highlighted_sector = std::string::npos;
};
}