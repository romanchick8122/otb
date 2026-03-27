#include "assert.h"

#include <raylib.h>

namespace otb
{
void handle_assert()
{
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
        ToggleBorderlessWindowed();
    __debugbreak();
}
}