#include "debug/assert.h"

#include <cstdio>
#include <cstdlib>

#include "io/terminal.h"

namespace monster_hub {

void assert_impl(
        bool exprValue, const char* expr, const char* file, uint64_t line)
{
    if (exprValue) return;

    char buffer[256] = {};
    snprintf(buffer, 256, "[ASSERT] %s:%llu: %s\n", file, line, expr);
    printToTerminal(buffer);

    abort();
}

} // namespace monster_hub

