#pragma once

#include "core/assert.h"

#include <memory>

namespace otb
{
class Component
{
  public:
    virtual ~Component() = default;
};

using ComponentPtr = std::weak_ptr<Component>;

template<class To>
To component_cast(Component* from)
{
    To result = dynamic_cast<To>(from);
    OTB_ASSERT(from == nullptr || result != nullptr);
    return result;
}
}