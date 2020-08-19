#include "util/unreachable.h"

#include <cstdio>
#include <cstdlib>

namespace monster_hub {

[[noreturn]]
void unreachable(const char* message)
{
    printf("UNREACHABLE - %s\n", message);
    abort();
}

} // namespace monster_hub

