#pragma once

#include "logging/logger.h"

#define LOG_INFO(...) LOG_INFO_IMPL(monster_hub::CHANNEL_DEBUG, __VA_ARGS__)
#define LOG_WARNING(...) LOG_WARNING_IMPL(monster_hub::CHANNEL_DEBUG, __VA_ARGS__)
#define LOG_ERROR(...) LOG_ERROR_IMPL(monster_hub::CHANNEL_DEBUG, __VA_ARGS__)
#define LOG_DEBUG(...) LOG_DEBUG_IMPL(monster_hub::CHANNEL_DEBUG, __VA_ARGS__)

