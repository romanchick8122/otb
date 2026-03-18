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

void Entity::set_name(InternedString _name)
{
    OTB_ASSERT(_name != InternedString::get_empty());
    if (name != InternedString::get_empty())
    {
        world->entities_by_name.erase(name);
    }
    name = _name;
    world->entities_by_name.emplace(name, this);
}

namespace
{
    static const InternedString COMPONENTS_FIELD { "components" };
    static const InternedString NAME_FIELD { "name" };
}

ValueStorage Entity::serialize() const
{
    ValueStorage::DictType components_vs;
    for (const auto& [ctype, component] : components)
    {
        components_vs.emplace(World::get_component_type_name(component.get()), component->serialize());
    }
    return ValueStorage::DictType {
        { NAME_FIELD, std::string{name.c_str()} },
        { COMPONENTS_FIELD, std::move(components_vs) },
    };
}

void Entity::deserialize(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    set_name(InternedString(std::get<std::string>(dict.at(NAME_FIELD).storage).c_str()));

    const auto& components_vs = dict.at(COMPONENTS_FIELD);
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(components_vs.storage));
    const auto& component_descriptors = std::get<ValueStorage::DictType>(components_vs.storage);
    for (const auto& [key, desc] : component_descriptors)
    {
        add_component(World::deserialize_component(key, desc));
    }
}
}