#include "logging/logger.h"

#include <cstdio>

#include "io/filesystem.h"
#include "io/terminal.h"
#include "util/unreachable.h"

namespace monster_hub {

namespace {

constexpr const char* toString(SeverityLevel level)
{
    switch (level)
    {
        case LEVEL_INFO:    return "info";
        case LEVEL_WARNING: return "warning";
        case LEVEL_ERROR:   return "error";
        case LEVEL_DEBUG:   return "debug";
        default: unreachable("Unknown severity level");
    }
}

constexpr const char* toString(LogChannel channel)
{
    switch (channel)
    {
        case CHANNEL_DEBUG: return "DEBUG";
        case CHANNEL_RENDERING: return "RENDERING";
        default: unreachable("unknown log channel");
    }
}

#if DEBUG_OPTION_ENABLED(LOG_TO_TERMINAL)

constexpr const char* fileName(LogChannel channel)
{
    switch (channel)
    {
        case CHANNEL_DEBUG: return "logs/debug.log";
        case CHANNEL_RENDERING: return "logs/rendering.log";
        default: unreachable("Unknown log channel");
    }
}

bool prepareLogFiles()
{
    for (int32_t i = 0; i < CHANNEL_COUNT; ++i)
    {
        remove(fileName(static_cast<LogChannel>(i)));
    }
    rmdir("logs");
    if (!mkdir("logs"))
    {
        printToTerminal("ERROR: Unable to create directory 'logs'\n");
        return false;
    }

    return true;
}

#define PREPARE_LOG_FILES() prepareLogFiles()

void writeToFile(const char* fileName, const char* message)
{
    FILE* file = fopen(fileName, "a");
    if (file == nullptr)
    {
        char buffer[256] = {};
        snprintf(buffer, 256, "ERROR: Could not open file '%s'\n", fileName);
        printToTerminal(buffer);
        return;
    }

    if (fputs(message, file) == EOF)
    {
        char buffer[256] = {};
        snprintf(buffer, 256, "ERROR: Could not write to file '%s'\n", fileName);
        printToTerminal(buffer);
    }

    fclose(file);
}

#define LOG_TO_TERMINAL(message) printToTerminal(message)

#else

#define PREPARE_LOG_FILES() 0
#define LOG_TO_TERMINAL(message)

#endif

} // namespace

#if DEBUG_OPTION_ENABLED(LOG_TO_FILE)
#define LOG_TO_FILE(file, message) writeToFile(file, message)
#else
#define LOG_TO_FILE(file, message)
#endif

int32_t initLog()
{
    return PREPARE_LOG_FILES();
}

void log(
        SeverityLevel level,
        LogChannel    channel,
        const char*   formatMsg,
        ...)
{
    va_list args;
    va_start(args, formatMsg);
    
    char formatMsgWithLevel[256] = {};
    snprintf(formatMsgWithLevel, 256, "%s: %s\n", toString(level), formatMsg);

    char messageWithLevel[512] = {};
    vsnprintf(messageWithLevel, 512, formatMsgWithLevel, args);

    va_end(args);

    char messageWithChannel[1024] = {};
    snprintf(messageWithChannel, 1024, "[%s] %s", toString(channel), messageWithLevel);

    LOG_TO_TERMINAL(messageWithChannel);
    LOG_TO_FILE(fileName(channel), messageWithLevel);
}

} // namespace monster_hub

