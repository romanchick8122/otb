#pragma once

#include "core/ecs/entity.h"
#include "core/ecs/component.h"

#include <chrono>
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

    float fixed_frame_time;
    size_t max_fixed_frames;

    void update();

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

    ValueStorage serialize() const;
    void deserialize(const ValueStorage&);

  private:
    float accumulated_time = 0.f;
    
    std::chrono::high_resolution_clock clock;
    decltype(clock.now()) previous_update_time;

    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<std::type_index, std::vector<ComponentPtr>> components;

    std::vector<FixedSystem> fixed_systems;
    std::vector<NormalSystem> normal_systems;

    friend class Entity;

    void register_component(const std::shared_ptr<Component>&);

  public:
    static void register_component_type(const char*, Component*(*)(const ValueStorage&), std::type_index);
    static InternedString get_component_type_name(Component*);
    static Component* deserialize_component(InternedString, const ValueStorage&);
};
}

#define REGISTER_COMPONENT_TYPE(T) ::otb::World::register_component_type(#T, T::deserialize, std::type_index(typeid(T)));

#include "world_impl.h"