#include "input.h"
#include "io/filesystem.h"
#include "logging/logger.h"
#include "math/matrix.h"
#include "math/vec2.h"
#include "rendering/projection.h"
#include "rendering/renderer.h"
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

    while (!isWindowClosed())
    {
        Vec2 cursorPos = getCursorPos();

        beginRendering();
        if (isMouseButtonDown(BUTTON_LEFT) &&
                cursorPos.x >= 160 && cursorPos.x <= 480 &&
                cursorPos.y >= 120 && cursorPos.y <= 360)
            pushQuad(160, 120, 320, 240, 1, 0, 0, 1);
        else
            pushQuad(160, 120, 320, 240, 0, 0, 1, 1);
        endRendering();
    }

    destroyRenderer();
    destroyWindow();
}

