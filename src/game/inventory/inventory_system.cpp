#include "inventory_system.h"

#include "core/ecs/world.h"

#include "game/character/character_component.h"
#include "game/inventory/inventory_component.h"

namespace game
{
void InventorySystem::init(otb::World* world)
{
    for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
    {
        it->entity->add_component(new InventoryComponent());
    }
}
}