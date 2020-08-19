#include "io/filesystem.h"
#include "io/terminal.h"

#include <direct.h>
#include <windows.h>

namespace monster_hub {

void printToTerminal(const char* message)
{
    OutputDebugString(message);
}

char PATH_SEPARATOR_CHAR = '\\';

bool mkdir(const char* path)
{
    return CreateDirectory(path, nullptr);
}

bool rmdir(const char* path)
{
    return RemoveDirectory(path);
}

bool chdir(const char* path)
{
    return !_chdir(path);
}

} // namespace monster_hub

