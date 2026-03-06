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

    world->register_component(it->second);
    return ComponentPtr(it->second);
}
}