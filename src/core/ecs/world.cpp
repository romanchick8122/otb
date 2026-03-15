#include "world.h"

namespace
{
    static std::unordered_map<otb::InternedString, otb::Component*(*)(const otb::ValueStorage&)> component_deserialiers;
    static std::unordered_map<std::type_index, otb::InternedString> component_type_names;
}

namespace otb
{
World::World()
{
    std::ignore = add_entity();

    previous_update_time = clock.now();
}

void World::update()
{
    const float frame_time = [this] {
        const auto current_time = clock.now();
        const auto time_delta = current_time - previous_update_time;
        previous_update_time = current_time;
        return std::min(std::chrono::nanoseconds(time_delta).count() / 1e9f, 1.f);
    }();

    accumulated_time += frame_time;
    for (uint32_t i = 0; accumulated_time > 0.f && i < max_fixed_frames; ++i)
    {
        fixed_update();
        accumulated_time -= fixed_frame_time;
    }
    normal_update(frame_time);
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

namespace
{
    static const InternedString ENTITIES_FIELD { "entities" };
}

ValueStorage World::serialize() const
{
    ValueStorage::ArrayType result;
    for (const auto& entity_ptr : entities)
    {
        result.emplace_back(entity_ptr->serialize());
    }

    return ValueStorage::DictType {
        { ENTITIES_FIELD, std::move(result) },
    };
}

void World::deserialize(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    const ValueStorage& entities_vs = dict.at(ENTITIES_FIELD);
    OTB_ASSERT(std::holds_alternative<ValueStorage::ArrayType>(entities_vs.storage));
    const auto& entities = std::get<ValueStorage::ArrayType>(entities_vs.storage);

    get_world_entity()->deserialize(entities[0]);
    for (size_t i = 1; i < entities.size(); ++i)
    {
        add_entity()->deserialize(entities[i]);
    }
}

void World::register_component(const std::shared_ptr<Component>& ptr)
{
    const Component& component = *ptr;
    const auto [map_entry, was_new] = components.try_emplace(std::type_index(typeid(component)));
    map_entry->second.emplace_back(ComponentPtr(ptr));
}

void World::register_component_type(const char* type, Component*(*deserializer)(const ValueStorage&), std::type_index tid)
{
    InternedString name { type };
    component_deserialiers.emplace(name, deserializer);
    component_type_names.emplace(tid, name);
}

InternedString World::get_component_type_name(Component* c)
{
    const Component& component = *c;
    if (const auto it = component_type_names.find(std::type_index(typeid(component)));
        it != component_type_names.end())
    {
        return it->second;
    }
    OTB_ASSERT(false);
    return InternedString::get_empty();
}

Component* World::deserialize_component(InternedString type_name, const ValueStorage& vs)
{
    if (const auto it = component_deserialiers.find(type_name);
        it != component_deserialiers.end())
    {
        return it->second(vs);   
    }

    OTB_ASSERT(false);
    return nullptr;
}
}