#pragma once

#include <cstdint>

#include "defines.h"

namespace monster_hub {

void assert_impl(
        bool exprValue, const char* expr, const char* file, uint64_t line);

#if DEBUG_FEATURE_ENABLED(ASSERT)

#define assert(expr) \
    monster_hub::assert_impl((expr), #expr, __FILE__, __LINE__)

#else

#define assert(expr)

#endif

} // namespace monster_hub

