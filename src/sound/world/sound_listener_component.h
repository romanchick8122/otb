#pragma once

#include "core/ecs/component.h"

#include <AK/SoundEngine/Common/AkTypedefs.h>

namespace otb
{
class SoundListenerComponent : public Component
{
    AkUInt64 object_id;
  public:
    SoundListenerComponent();
    ~SoundListenerComponent() override;
};
}