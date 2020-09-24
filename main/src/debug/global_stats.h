#pragma once

#include <cstdint>

#include "defines.h"

namespace monster_hub {

#if DEBUG_FEATURE_ENABLED(STATISTICS) && DEBUG_OPTION_ENABLED(GLOBAL_COUNTER)

enum GlobalCounterIntId : uint32_t
{
    GLOBAL_COUNTER_I_DEBUG,
    GLOBAL_COUNTER_I_COUNT
};

constexpr const char* globalCounterIntNames[GLOBAL_COUNTER_I_COUNT] = {
    "Debug int global counter"
};

enum GlobalCounterFltId : uint32_t
{
    GLOBAL_COUNTER_F_DEBUG,
    GLOBAL_COUNTER_F_COUNT
};

constexpr const char* globalCounterFltNames[GLOBAL_COUNTER_F_COUNT] = {
    "Debug float global counter"
};

const char* getGlobalCounterNameI_impl(GlobalCounterIntId id);
const char* getGlobalCounterNameF_impl(GlobalCounterFltId id);

uint64_t& getGlobalCounterI_impl(GlobalCounterIntId id);
double& getGlobalCounterF_impl(GlobalCounterFltId id);

#define PUSH_TO_GLOBAL_COUNTER_I(id, val) \
    (getGlobalCounterI_impl(GLOBAL_COUNTER_I_##id) += val)
#define PUSH_TO_GLOBAL_COUNTER_F(id, val) \
    (getGlobalCounterF_impl(GLOBAL_COUNTER_F_##id) += val)

#define GET_GLOBAL_COUNTER_I(id) getGlobalCounterI_impl(GLOBAL_COUNTER_I_##id)
#define GET_GLOBAL_COUNTER_F(id) getGlobalCounterF_impl(GLOBAL_COUNTER_I_##id)

#define GET_GLOBAL_COUNTER_NAME_I(id) \
    getGlobalCounterNameI_impl(GLOBAL_COUNTER_I_##id)
#define GET_GLOBAL_COUNTER_NAME_F(id) \
    getGlobalCounterNameF_impl(GLOBAL_COUNTER_F_##id)

#else

#define PUSH_TO_GLOBAL_COUNTER_I(id, val)
#define PUSH_TO_GLOBAL_COUNTER(id, val)

#define GET_GLOBAL_COUNTER_I(id)
#define GET_GLOBAL_COUNTER_F(id)

#define GET_GLOBAL_COUNTER_NAME_I(id)
#define GET_GLOBAL_COUNTER_NAME_F(id)

#endif

} // namespace monster_hub

