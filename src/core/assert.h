#include <cassert>

#define OTB_ASSERT(EXPR) \
if (!(EXPR)) [[unlikely]] \
{ \
    __debugbreak(); \
    assert(EXPR); \
}