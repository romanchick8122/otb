#include <cassert>

#include <raylib.h>

#if defined(OTB_DEBUG)
#define OTB_ASSERT(EXPR) \
do { if (!(EXPR)) [[unlikely]] \
{ \
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) ToggleBorderlessWindowed(); \
    __debugbreak(); \
    assert(EXPR); \
}}while(0)
#else
#define OTB_ASSERT(EXPR) \
_Pragma(R"(clang diagnostic push)") \
_Pragma(R"(clang diagnostic ignored "-Wassume")") \
[[assume(EXPR)]] \
_Pragma(R"(clang diagnostic pop)")
#endif