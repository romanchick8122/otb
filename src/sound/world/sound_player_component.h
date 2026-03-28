#pragma once

#include "core/ecs/component.h"

#include <AK/SoundEngine/Common/AkTypedefs.h>

namespace otb
{
class SoundPlayerComponent : public Component
{
    AkUInt64 object_id;

  public:
    SoundPlayerComponent();
    ~SoundPlayerComponent() override;

    void play_event(AkUniqueID) const;
};
}