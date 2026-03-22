#include "inventory_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/render/model_component.h"
#include "core/world/transform_component.h"

#include "game/character/character_component.h"
#include "game/inventory/inventory_component.h"
#include "game/inventory/item_pickup_component.h"

namespace game
{
namespace
{
    static const otb::InternedString ITEM_PICKUP_IDLE_ANIMATION("ArmatureAction");
    static constexpr float ANIMATION_SPEED = 60.f;
}

void InventorySystem::init(otb::World* world)
{
    using namespace otb;

    for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
    {
        it->entity->add_component(new InventoryComponent());
    }

    for (auto it = world->components_begin<ItemPickupComponent>(); it != world->components_end<ItemPickupComponent>(); ++it)
    {
        auto* pickup_model = it->entity->get_component<ModelComponent>();
        pickup_model->request_animation(ITEM_PICKUP_IDLE_ANIMATION, true);
        pickup_model->set_animation_speed(ANIMATION_SPEED);
    }
}

void InventorySystem::process_item_pickup(otb::World* world)
{
    using namespace otb;
    for (auto inventory_it = world->components_begin<InventoryComponent>(); inventory_it != world->components_end<InventoryComponent>(); ++inventory_it)
    {
        const Transform& inventory_transform = inventory_it->entity->get_component<TransformComponent>()->transform;
        for (auto pickup_it = world->components_begin<ItemPickupComponent>(); pickup_it != world->components_end<ItemPickupComponent>(); ++pickup_it)
        {
            if (!pickup_it->pickup_active)
            {
                continue;
            }

            const Vector3 pickup_space = TransformUtils::apply_inverse_transform(pickup_it->entity->get_component<TransformComponent>()->transform, inventory_transform.translation);
            static const BoundingBox default_collider {
                .min = { -0.5f, -0.5f, -0.5f },
                .max = { 0.5f, 0.5f, 0.5f },
            };
            if (TransformUtils::is_point_in_bounding_box(pickup_space, default_collider))
            {
                inventory_it->items.emplace(pickup_it->item);
                pickup_it->pickup_active = false;
                pickup_it->entity->get_component<ModelComponent>()->hide();
                // TODO: temporary activation
                inventory_it->active_item = pickup_it->item;
            }
        }
    }
}
}