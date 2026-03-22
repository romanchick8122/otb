#include "inventory_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/render/model_component.h"
#include "core/world/transform_component.h"

#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"
#include "game/inventory/inventory_component.h"
#include "game/inventory/item_pickup_component.h"

#include <raymath.h>

namespace game
{
namespace
{
    static const otb::InternedString ITEM_PICKUP_IDLE_ANIMATION("ArmatureAction");
    static constexpr float ANIMATION_SPEED = 60.f;

    static constexpr float MOUSE_DEAD_ZONE = 3000.f;
    static constexpr size_t SECTOR_COUNT = 3uz;
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
                inventory_it->items.emplace_back(pickup_it->item);
                pickup_it->pickup_active = false;
                pickup_it->entity->get_component<ModelComponent>()->hide();
            }
        }
    }
}

void InventorySystem::process_hud(otb::World* world)
{
    for (auto inventory_it = world->components_begin<InventoryComponent>(); inventory_it != world->components_end<InventoryComponent>(); ++inventory_it)
    {
        const bool was_open = inventory_it->hud_open;

        const auto* input_receiver_component = inventory_it->entity->get_component<InputReceiverComponent>();

        if (inventory_it->entity->get_component<CharacterComponent>()->movement_state != CharacterComponent::MovementState::GROUNDED)
        {
            inventory_it->hud_open = false;
        }
        else
        {
            inventory_it->hud_open = input_receiver_component->extra_actions.contains(InputReceiverComponent::ActionNames::inventory);
        }

        if (!inventory_it->hud_open)
        {
            if (was_open && inventory_it->hud_highlighted_sector != std::string::npos && (SECTOR_COUNT - 1uz - inventory_it->hud_highlighted_sector) < inventory_it->items.size())
            {
                inventory_it->active_item = inventory_it->items[SECTOR_COUNT - 1uz - inventory_it->hud_highlighted_sector];
            }
            continue;
        }

        if (!was_open)
        {
            inventory_it->hud_highlighted_sector = std::string::npos;
        }

        if (Vector2LengthSqr(input_receiver_component->secondary_analog_input) < MOUSE_DEAD_ZONE * MOUSE_DEAD_ZONE * world->fixed_frame_time * world->fixed_frame_time)
        {
            continue;
        }

        const float angle = fmod(atan2(-input_receiver_component->secondary_analog_input.y, -input_receiver_component->secondary_analog_input.x) + 2.f * PI, 2.f * PI);
        inventory_it->hud_highlighted_sector = static_cast<size_t>(angle * static_cast<float>(SECTOR_COUNT) / 2.f / PI);
    }
}
}