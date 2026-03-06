#pragma once

#include "core/asset/value_storage.h"
#include "core/assert.h"

#include <memory>

namespace otb
{
class Entity;

class Component
{
  public:
    virtual ValueStorage serialize() const;

    virtual ~Component() = default;

    Entity* entity;
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