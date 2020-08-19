#include <cstdio>

#include "io/filesystem.h"
#include "io/terminal.h"
#include "logging/logger.h"

int main(int, char* argv[])
{
    char buffer[128] = {};
    monster_hub::dirname(buffer, 128, argv[0]);
    monster_hub::chdir(buffer);

    char terminalBuffer[256] = {};
    snprintf(terminalBuffer, 256, "dirname=%s\n", buffer);
    monster_hub::printToTerminal(terminalBuffer);

    INIT_LOG();

    LOG(monster_hub::LEVEL_INFO, monster_hub::CHANNEL_DEBUG,
        "Hello, %s!", "World");

    for (int i = 1; i < 11; ++i)
    {
        LOG(monster_hub::LEVEL_DEBUG, monster_hub::CHANNEL_DEBUG,
            "Log message %d", i);
    }
}

