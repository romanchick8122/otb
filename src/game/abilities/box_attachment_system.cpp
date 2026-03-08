#include "box_attachment_system.h"

#include "core/ecs/world.h"
#include "core/ecs/component.h"
#include "core/math/transform_utils.h"
#include "core/world/transform_component.h"

#include "game/box/box_component.h"
#include "game/box/box_system.h"
#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"

#include "raymath.h"

namespace game
{
namespace
{
struct BoxAttachmentAbilityComponent : public otb::Component
{
    ~BoxAttachmentAbilityComponent() = default;

    bool prev_frame_button_active = false;
    BoxComponent* attached_box = nullptr;
};
}

void BoxAttachmentSystem::process_ability_activation(otb::World* world)
{
    using namespace otb;

    const auto* character_input_receiver = world->components_begin<CharacterComponent>()->entity->get_component<InputReceiverComponent>();

    BoxAttachmentAbilityComponent* ability = character_input_receiver->entity->get_component<BoxAttachmentAbilityComponent>();
    if (ability == nullptr) [[unlikely]]
    {
        ability = new BoxAttachmentAbilityComponent();
        character_input_receiver->entity->add_component(ability);
    }

    if (character_input_receiver->extra_actions.count(InputReceiverComponent::ActionNames::ability_1) == 0)
    {
        ability->prev_frame_button_active = false;
        return;
    }

    if (ability->prev_frame_button_active)
    {
        return;
    }

    ability->prev_frame_button_active = true;

    // Detach
    if (ability->attached_box != nullptr)
    {
        ability->attached_box = nullptr;
        return;
    }

    // Attach
    TransformComponent* character_transform = character_input_receiver->entity->get_component<TransformComponent>();
    const Ray character_look_ray {
        .position = character_transform->transform.translation,
        .direction = Vector3RotateByQuaternion(Vector3{1, 0, 0}, character_transform->transform.rotation),
    };

    std::pair<RayCollision, BoxComponent*> best_hit{ {}, nullptr };
    for (auto box_it = world->components_begin<BoxComponent>(); box_it != world->components_end<BoxComponent>(); ++box_it)
    {
        if (box_it->entity == character_input_receiver->entity)
        {
            continue;
        }

        const BoundingBox box = TransformUtils::get_box(box_it->entity->get_component<TransformComponent>()->transform);
        RayCollision collision = GetRayCollisionBox(character_look_ray, box);
        if (!collision.hit)
        {
            continue;
        }
        if (best_hit.second == nullptr || best_hit.first.distance > collision.distance)
        {
            best_hit = { collision, &*box_it};
        }
    }
    if (best_hit.second != nullptr)
    {
        ability->attached_box = best_hit.second;
    }
}

void BoxAttachmentSystem::process_ability(otb::World* world)
{
    using namespace otb;

    auto* box_sc = world->get_world_entity()->get_component<BoxSingleComponent>();
    for (auto it = world->components_begin<BoxAttachmentAbilityComponent>(); it != world->components_end<BoxAttachmentAbilityComponent>(); ++it)
    {
        if (it->attached_box != nullptr)
        {
            box_sc->request_one_frame_attachment(it->attached_box);
        }
    }
}

void BoxAttachmentSystem::debug_draw(otb::World* world, float)
{
    using namespace otb;

    BoxAttachmentAbilityComponent* ability = world->components_begin<CharacterComponent>()->entity->get_component<BoxAttachmentAbilityComponent>();
    if (ability == nullptr) [[unlikely]]
    {
        return;
    }
    if (ability->attached_box == nullptr)
    {
        return;
    }

    const Vector3 from = ability->entity->get_component<TransformComponent>()->transform.translation;
    const Vector3 to = ability->attached_box->entity->get_component<TransformComponent>()->transform.translation;
    DrawLine3D(from, to, YELLOW);
}
}