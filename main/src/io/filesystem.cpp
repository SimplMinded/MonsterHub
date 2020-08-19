#include "io/filesystem.h"

#include <cstring>

namespace monster_hub {

bool dirname(char* result, size_t resultSize, const char* path)
{
    const char* ptr = strrchr(path, PATH_SEPARATOR_CHAR);
    size_t dirnameSize = static_cast<size_t>(ptr - path);
    if (resultSize <= dirnameSize) return false;
    memcpy(result, path, dirnameSize);
    return true;
}

} // namespace monster_hub

