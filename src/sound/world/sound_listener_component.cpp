#include "sound_listener_component.h"

#include "sound/sound_engine.h"

#include <AK/SoundEngine/Common/AkSoundEngine.h>

namespace otb
{
SoundListenerComponent::SoundListenerComponent()
    : object_id(SoundEngine::instance()->create_game_object())
{
    AK::SoundEngine::RegisterGameObj(object_id);
    AK::SoundEngine::SetDefaultListeners(&object_id, 1);
}

SoundListenerComponent::~SoundListenerComponent()
{
    AK::SoundEngine::RemoveDefaultListener(object_id);
    AK::SoundEngine::UnregisterGameObj(object_id);
}
}