#pragma once

#include "core/interned_string.h"

namespace otb
{
class SoundEngine
{
    SoundEngine();
    size_t free_id = 1;

  public:
    ~SoundEngine();

    void update() const;

    void load_bank(InternedString bank_name);
    size_t create_game_object();

    static SoundEngine* instance();
};
}