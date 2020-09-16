#include "debug/statistics.h"

#include "debug/assert.h"
#include "util/array.h"

namespace monster_hub {

#if DEBUG_FEATURE_ENABLED(STATISTICS)

namespace {

Array<uint64_t, GLOBAL_COUNTER_I_COUNT> globalIntCounters = {};
Array<double, GLOBAL_COUNTER_F_COUNT> globalFltCounters = {};

size_t currentFrame = 0;

constexpr size_t frame_counter_i_array_count =
    FRAME_COUNTER_I_COUNT * frame_counter_capacity;
constexpr size_t frame_counter_f_array_count =
    FRAME_COUNTER_F_COUNT * frame_counter_capacity;

Array<uint64_t, frame_counter_i_array_count> frameIntCounters = {};
Array<double, frame_counter_f_array_count> frameFltCounters = {};

} // namespace

const char* getGlobalCounterNameI_impl(GlobalCounterIntId id)
{
    assert(id < GLOBAL_COUNTER_I_COUNT);

    return globalCounterIntNames[id];
}

const char* getGlobalCounterNameF_impl(GlobalCounterFltId id)
{
    assert(id < GLOBAL_COUNTER_F_COUNT);

    return globalCounterFltNames[id];
}

uint64_t& getGlobalCounterI_impl(GlobalCounterIntId id)
{
    return globalIntCounters[id];
}

double& getGlobalCounterF_impl(GlobalCounterFltId id)
{
    return globalFltCounters[id];
}

const char* getFrameCounterNameI_impl(FrameCounterIntId id)
{
    assert(id < FRAME_COUNTER_I_COUNT);

    return frameCounterIntNames[id];
}

const char* getFrameCounterNameF_impl(FrameCounterFltId id)
{
    assert(id < FRAME_COUNTER_F_COUNT);

    return frameCounterFltNames[id];
}

uint64_t& getFrameCounterI_impl(FrameCounterIntId id)
{
    assert(id < FRAME_COUNTER_I_COUNT);

    return frameIntCounters[(id * frame_counter_capacity) + 
        (currentFrame % frame_counter_capacity)];
}

double& getFrameCounterF_impl(FrameCounterFltId id)
{
    assert(id < FRAME_COUNTER_F_COUNT);

    return frameFltCounters[(id * frame_counter_capacity) +
        (currentFrame % frame_counter_capacity)];
}

void updateFrameStats_impl()
{
    currentFrame++;
    for (uint32_t i = 0; i < FRAME_COUNTER_I_COUNT; ++i)
    {
        getFrameCounterI_impl(static_cast<FrameCounterIntId>(i)) = 0;
    }
    for (uint32_t i = 0; i < FRAME_COUNTER_F_COUNT; ++i)
    {
        getFrameCounterF_impl(static_cast<FrameCounterFltId>(i)) = 0;
    }
}

size_t getCurrentFrame_impl()
{
    return currentFrame;
}

uint64_t getCounterAt(const FrameStatsInt& stats, size_t index)
{
    assert(index < frame_counter_capacity);

    return stats.counters[(stats.firstIndex + index) % frame_counter_capacity];
}

double getCounterAt(const FrameStatsFlt& stats, size_t index)
{
    assert(index < frame_counter_capacity);

    return stats.counters[(stats.firstIndex + index) % frame_counter_capacity];
}

FrameStatsInt getFrameStatsI_impl(FrameCounterIntId id)
{
    assert(id < FRAME_COUNTER_I_COUNT);

    return {
        &frameIntCounters[id * frame_counter_capacity],
        currentFrame > frame_counter_capacity ?
            (currentFrame + 1) % frame_counter_capacity :
            0
    };
}

FrameStatsFlt getFrameStatsF_impl(FrameCounterFltId id)
{
    assert(id < FRAME_COUNTER_F_COUNT);

    return {
        &frameFltCounters[id * frame_counter_capacity],
        currentFrame > frame_counter_capacity ?
            (currentFrame +1) % frame_counter_capacity :
            0
    };
}

#endif

} // namespace monster_hub

