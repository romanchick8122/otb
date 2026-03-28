#include "event_trigger_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/world/transform_component.h"

#include "game/character/character_component.h"
#include "game/menu/event_trigger_component.h"
#include "game/menu/upstream_interaction_component.h"

#include "sound/world/sound_player_component.h"

#include "../assets/sound/Wwise_IDs.h"

namespace game
{
void EventTriggerSystem::fixed_update(otb::World* world)
{
    using namespace otb;

    auto* upstream_interaction = world->get_world_entity()->get_component<UpstreamInteractionComponent>();

    const auto* character = world->components_begin<CharacterComponent>()->entity;
    const Vector3 character_world_position = character->get_component<TransformComponent>()->transform.translation;
    for (auto it = world->components_begin<EventTriggerComponent>(); it != world->components_end<EventTriggerComponent>(); ++it)
    {
        const Vector3 character_local = TransformUtils::apply_inverse_transform(it->entity->get_component<TransformComponent>()->transform, character_world_position);
        if (TransformUtils::is_point_in_bounding_box(character_local, {
            .min = {-0.5f, -0.5f, -0.5f},
            .max = {0.5f, 0.5f, 0.5f},
        }))
        {
            upstream_interaction->events.emplace_back(it->inside_event);
            character->get_component<SoundPlayerComponent>()->play_event(AK::EVENTS::PLAY_LEVEL_END_SOUND);
        }
    }
}
}