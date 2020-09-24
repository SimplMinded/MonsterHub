#pragma once

#include <cstddef>
#include <cstdint>

#include "defines.h"

namespace monster_hub {

#if DEBUG_FEATURE_ENABLED(STATISTICS) && DEBUG_OPTION_ENABLED(FRAME_COUNTER)

constexpr size_t frame_counter_capacity = 60 * 600;

enum FrameCounterIntId : uint32_t
{
    FRAME_COUNTER_I_DEBUG,
    FRAME_COUNTER_I_COUNT
};

constexpr const char* frameCounterIntNames[FRAME_COUNTER_I_COUNT] = {
    "Debug int frame counter"
};

enum FrameCounterFltId : uint32_t
{
    FRAME_COUNTER_F_DEBUG,
    FRAME_COUNTER_F_COUNT
};

constexpr const char* frameCounterFltNames[FRAME_COUNTER_F_COUNT] = {
    "Debug float frame counter"
};

const char* getFrameCounterNameI_impl(FrameCounterIntId id);
const char* getFrameCounterNameF_impl(FrameCounterFltId id);

uint64_t& getFrameCounterI_impl(FrameCounterIntId id);
double& getFrameCounterF_impl(FrameCounterFltId id);

void updateFrameStats_impl();
size_t getCurrentFrame_impl();

struct FrameStatsInt
{
    uint64_t* counters;
    size_t firstIndex;
};

uint64_t getCounterAt(const FrameStatsInt& stats, size_t index);

FrameStatsInt getFrameStatsI_impl(FrameCounterIntId id);

struct FrameStatsFlt
{
    double* counters;
    size_t firstIndex;
};

double getCounterAt(const FrameStatsFlt& stats, size_t index);

FrameStatsFlt getFrameStatsF_impl(FrameCounterFltId id);

#define PUSH_TO_FRAME_COUNTER_I(id, val) \
    (getFrameCounterI_impl(FRAME_COUNTER_I_##id) += val)
#define PUSH_TO_FRAME_COUNTER_F(id, val) \
    (getFrameCounterF_impl(FRAME_COUNTER_F_##id) += val)

#define GET_FRAME_COUNTER_I(id) getFrameCounterI_impl(FRAME_COUNTER_I_##id)
#define GET_FRAME_COUNTER_F(id) getFrameCounterF_impl(FRAME_COUNTER_F_##id)

#define GET_FRAME_COUNTER_NAME_I(id) \
    getFrameCounterNameI_impl(FRAME_COUNTER_I_##id)
#define GET_FRAME_COUNTER_NAME_F(id) \
    getFrameCounterNameF_impl(FRAME_COUNTER_F_##id)

#define UPDATE_FRAME_STATS() updateFrameStats_impl()
#define GET_CURRENT_FRAME() getCurrentFrame_impl()

#define GET_FRAME_STATS_I(id) getFrameStatsI_impl(FRAME_COUNTER_I_##id)
#define GET_FRAME_STATS_F(id) getFrameStatsF_impl(FRAME_COUNTER_F_##id)

#else

#define PUSH_TO_FRAME_COUNTER_I(id, val)
#define PUSH_TO_FRAME_COUNTER_F(id, val)

#define GET_FRAME_COUNTER_I(id)
#define GET_FRAME_COUNTER_F(id)

#define GET_FRAME_COUNTER_NAME_I(id)
#define GET_FRAME_COUNTER_NAME_F(id)

#define UPDATE_FRAME_STATS()
#define GET_CURRENT_FRAME()

#define GET_FRAME_STATS_I(id)
#define GET_FRAME_STATS_F(id)

#endif

} // namespace monster_hub

