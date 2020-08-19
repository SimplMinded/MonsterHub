#include "io/filesystem.h"
#include "io/terminal.h"

#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>

namespace monster_hub {

void printToTerminal(const char* message)
{
    printf("%s", message);
}

char PATH_SEPARATOR_CHAR = '/';

bool mkdir(const char* path)
{
    return !::mkdir(path, S_IRWXU | S_IRWXG | S_IXOTH);
}

bool rmdir(const char* path)
{
    return !remove(path);
}

bool chdir(const char* path)
{
    return !::chdir(path);
}

} // namespace monster_hub

