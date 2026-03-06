#include "entity.h"

#include "core/assert.h"
#include "core/ecs/world.h"

namespace otb
{
Entity::Entity(World* _world)
    : world(_world)
{
}

ComponentPtr Entity::add_component(Component* component)
{
    const std::type_index tid(typeid(*component));
    const auto [it, inserted] = components.try_emplace(tid, std::shared_ptr<Component>(component));

    OTB_ASSERT(inserted);
    OTB_ASSERT(it->first == tid);

    component->entity = this;
    world->register_component(it->second);
    return ComponentPtr(it->second);
}

ValueStorage Entity::serialize() const
{
    ValueStorage::DictType result;
    for (const auto& [ctype, component] : components)
    {
        result.emplace(World::get_component_type_name(component.get()), component->serialize());
    }
    return result;
}

void Entity::deserialize(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& component_descriptors = std::get<ValueStorage::DictType>(vs.storage);
    for (const auto& [key, desc] : component_descriptors)
    {
        add_component(World::deserialize_component(key, desc));
    }
}
}