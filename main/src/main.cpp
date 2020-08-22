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


    while (!isWindowClosed())
    {
        beginRendering();
        pushQuad(160, 120, 320, 240, 1, 0, 0, 1);
        endRendering();
    }

    destroyRenderer();
    destroyWindow();
}

