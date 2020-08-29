#include "input.h"
#include "io/filesystem.h"
#include "logging/logger.h"
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

    float projection[16] = {};
    orthogonalProjection(projection, 0, 640, 0, 480, -1, 1);

    initRenderer();
    setProjection(projection);

    float mouseX, mouseY;
    while (!isWindowClosed())
    {
        getCursorPos(mouseX, mouseY);

        beginRendering();
        if (isMouseButtonDown(BUTTON_LEFT) && mouseX >= 160 && mouseX <= 480 && mouseY >= 120 && mouseY <= 360)
            pushQuad(160, 120, 320, 240, 1, 0, 0, 1);
        else
            pushQuad(160, 120, 320, 240, 0, 0, 1, 1);
        endRendering();
    }

    destroyRenderer();
    destroyWindow();
}

