#pragma once

#include <cstddef>

#include "defines.h"

namespace monster_hub {

#if DEBUG_FEATURE_ENABLED(GL_ASSERT)

void glAssert_impl(const char* file, size_t line, const char* call);

#define GL_ASSERT(call) \
    while (glGetError() != GL_NO_ERROR); \
    call; \
    glAssert_impl(__FILE__, __LINE__, #call)

#else

#define GL_ASSERT(call) call

#endif


} // namespace monster_hub

