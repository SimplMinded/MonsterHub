#include <cstdio>

#include "debug/logger.h"
#include "debug/statistics.h"
#include "io/filesystem.h"
#include "io/image.h"
#include "logging/logger.h"
#include "math/matrix.h"
#include "math/vec2.h"
#include "rendering/color.h"
#include "rendering/font.h"
#include "rendering/image.h"
#include "rendering/projection.h"
#include "rendering/renderer.h"
#include "rendering/spritesheet.h"
#include "rendering/texture.h"
#include "rendering/texture_region.h"
#include "window.h"

using namespace monster_hub;

int main(int, char* argv[])
{
    char workingDir[128];
    dirname(workingDir, 128, argv[0]);
    chdir(workingDir);

    INIT_LOG();

    createWindow(640, 480, "Hello World");

    Matrix projection = orthogonalProjection(0, 640, 0, 480, -1, 1);

    initRenderer();
    setProjection(projection);

    Spritesheet font = createBitmapFont("oldschool", 7, 9);

    while (!isWindowClosed())
    {
        GLOBAL_COUNTER_I(DEBUG)++;

        beginRendering();

        char global[128] = {};
        snprintf(global, 128, "%s: %lu", GLOBAL_COUNTER_NAME_I(DEBUG), GLOBAL_COUNTER_I(DEBUG));
        pushText(0, 0, 25, global, font);

        FRAME_COUNTER_I(DEBUG) = CURRENT_FRAME();
        char frame[128] = {};
        snprintf(frame, 128, "%s: %lu", FRAME_COUNTER_NAME_I(DEBUG), FRAME_COUNTER_I(DEBUG));
        pushText(0, 25, 25, frame, font);

        FrameStatsInt stats = FRAME_STATS_I(DEBUG);
        for (uint32_t i = 0; i < 10; ++i)
        {
            size_t index = CURRENT_FRAME() > 10 ?
                (CURRENT_FRAME() - 10 + i) % frame_counter_capacity :
                i;

            char frames[128] = {};
            snprintf(frames, 128, "Frame %u: %lu", 10 - i, getCounterAt(stats, index));
            pushText(0, static_cast<float>(25 * (i + 2)), 25, frames, font);
        }

        endRendering();

        UPDATE_FRAME_STATS();
    }

    destroyBitmapFont(font);
    destroyRenderer();
    destroyWindow();
}

