#pragma once

#include <cstdarg>
#include <cstdint>

#include "defines.h"

namespace monster_hub {

enum SeverityLevel
{
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_DEBUG,
    LEVEL_COUNT
};

enum LogChannel
{
    CHANNEL_RENDERING,
    CHANNEL_COUNT
};

#if DEBUG_FEATURE_ENABLED(LOGGING)

int32_t initLog();

#define INIT_LOG() monster_hub::initLog()

void log(
        SeverityLevel level,
        LogChannel    channel,
        const char*   formatMsg,
        ...);

#define LOG(...) monster_hub::log(__VA_ARGS__)

#else

#define INIT_LOG()
#define LOG(...)

#endif

#define LOG_INFO_IMPL(...) LOG(monster_hub::LEVEL_INFO, __VA_ARGS__)
#define LOG_WARNING_IMPL(...) LOG(monster_hub::LEVEL_WARNING, __VA_ARGS__)
#define LOG_ERROR_IMPL(...) LOG(monster_hub::LEVEL_ERROR, __VA_ARGS__)
#define LOG_DEBUG_IMPL(...) LOG(monster_hub::LEVEL_DEBUG, __VA_ARGS__)

} // monster_hub

