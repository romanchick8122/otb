#pragma once

#include "core/interned_string.h"

#include <AK/SoundEngine/Common/AkTypedefs.h>

namespace otb
{
class SoundEngine
{
    SoundEngine();
    AkUInt64 free_id = 1;

  public:
    ~SoundEngine();

    void update() const;

    void load_bank(InternedString bank_name);
    AkUInt64 create_game_object();

    static SoundEngine* instance();
};
}