#include <cassert>

namespace otb
{
void handle_assert();
}

#if defined(OTB_DEBUG)
#define OTB_ASSERT(EXPR, ...) \
do { if (!(EXPR)) [[unlikely]] \
{ \
    ::otb::handle_assert(); \
    assert(EXPR); \
}}while(0)
#else
#define OTB_ASSERT(EXPR) \
_Pragma(R"(clang diagnostic push)") \
_Pragma(R"(clang diagnostic ignored "-Wassume")") \
[[assume(EXPR)]] \
_Pragma(R"(clang diagnostic pop)")
#endif