#pragma once

#include "core/ecs/component.h"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace otb
{
class World;

class Entity final
{
  public:
    ComponentPtr add_component(Component*);

    template<typename T>
    bool has_component()
    {
        return components.find(std::type_index(typeid(T))) != components.end();
    }

    template<typename T>
    T* get_component()
    {
        if (const auto it = components.find(std::type_index(typeid(T)));
            it != components.end())
        {
            return component_cast<T*>(it->second.get());
        }
        return nullptr;
    }
  private:
    Entity(World*);

    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;

    World* world = nullptr;

    friend class World;
};
}