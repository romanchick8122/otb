#include "world.h"

namespace otb
{
World::World()
{
    std::ignore = add_entity();
}

void World::fixed_update()
{
    for (const auto& system : fixed_systems)
    {
        system(this);
    }
}

void World::normal_update(float dt)
{
    for (const auto& system : normal_systems)
    {
        system(this, dt);
    }
}

Entity* World::get_world_entity() const
{
    return entities[0].get();
}

Entity* World::add_entity()
{
    Entity* result = new Entity(this);
    entities.emplace_back(result);
    return result;
}

void World::add_fixed_system(World::FixedSystem&& system)
{
    fixed_systems.emplace_back(std::move(system));
}

void World::add_normal_system(World::NormalSystem&& system)
{
    normal_systems.emplace_back(std::move(system));
}

void World::register_component(const std::shared_ptr<Component>& ptr)
{
    const Component& component = *ptr;
    const auto [map_entry, was_new] = components.try_emplace(std::type_index(typeid(component)));
    map_entry->second.emplace_back(ComponentPtr(ptr));
}
}