#pragma once

#include "core/ecs/entity.h"
#include "core/ecs/component.h"

#include <functional>
#include <optional>
#include <memory>
#include <typeindex>
#include <vector>
#include <unordered_map>

namespace otb
{
class World final
{
  public:
    World();

    void fixed_update();
    void normal_update(float dt);

    Entity* get_world_entity() const;
    Entity* add_entity();

    using FixedSystem = std::function<void(World*)>;
    using NormalSystem = std::function<void(World*, float)>;

    void add_fixed_system(FixedSystem&&);
    void add_normal_system(NormalSystem&&);

    template<class T>
    class ComponentIterator;
    template<class T>
    ComponentIterator<T> components_begin();
    template<class T>
    ComponentIterator<T> components_end();

  private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<std::type_index, std::vector<ComponentPtr>> components;

    std::vector<FixedSystem> fixed_systems;
    std::vector<NormalSystem> normal_systems;

    friend class Entity;

    void register_component(const std::shared_ptr<Component>&);
};
}

#include "world_impl.h"