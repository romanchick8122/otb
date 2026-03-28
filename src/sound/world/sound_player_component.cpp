#include "sound_player_component.h"

#include "sound/sound_engine.h"

#include <AK/SoundEngine/Common/AkSoundEngine.h>

namespace otb
{
SoundPlayerComponent::SoundPlayerComponent()
    : object_id(SoundEngine::instance()->create_game_object())
{
    AK::SoundEngine::RegisterGameObj(object_id);
}

SoundPlayerComponent::~SoundPlayerComponent()
{
    AK::SoundEngine::UnregisterGameObj(object_id);
}

void SoundPlayerComponent::play_event(AkUniqueID evt) const
{
      AK::SoundEngine::PostEvent(evt, object_id);
}
}