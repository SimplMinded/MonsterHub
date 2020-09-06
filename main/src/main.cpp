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
        beginRendering();
        pushText(0, 0, 50, "Hello!", font);
        endRendering();
    }

    destroyBitmapFont(font);
    destroyRenderer();
    destroyWindow();
}

