#include "io/filesystem.h"
#include "logging/logger.h"
#include "math/matrix.h"
#include "math/vec2.h"
#include "rendering/color.h"
#include "rendering/projection.h"
#include "rendering/renderer.h"
#include "rendering/spritesheet.h"
#include "rendering/texture.h"
#include "rendering/texture_region.h"
#include "window.h"

using namespace monster_hub;

static void setPixel(uint8_t* result, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    result[0] = r;
    result[1] = g;
    result[2] = b;
    result[3] = a;
}

static void createImage0(uint8_t* result)
{
    for (uint32_t i = 0; i < 6 * 9; ++i)
    {
        setPixel(&result[i * 4], 255, 255, 255, 255);
    }

    setPixel(&result[8 * 4], 0, 0, 255, 255);
    setPixel(&result[9 * 4], 0, 0, 255, 255);
    setPixel(&result[13 * 4], 0, 0, 255, 255);
    setPixel(&result[16 * 4], 0, 0, 255, 255);
    setPixel(&result[19 * 4], 0, 0, 255, 255);
    setPixel(&result[22 * 4], 0, 0, 255, 255);
    setPixel(&result[31 * 4], 0, 0, 255, 255);
    setPixel(&result[34 * 4], 0, 0, 255, 255);
    setPixel(&result[37 * 4], 0, 0, 255, 255);
    setPixel(&result[40 * 4], 0, 0, 255, 255);
    setPixel(&result[44 * 4], 0, 0, 255, 255);
    setPixel(&result[45 * 4], 0, 0, 255, 255);
}

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

    uint8_t image0[6 * 9 * 4] = {};
    createImage0(image0);
    Texture texture0 = createTexture(6, 9, image0);

    Spritesheet spritesheet = makeSpritesheet(texture0, 3);

    while (!isWindowClosed())
    {
        beginRendering();
        pushQuad(0, 120, 160, 240, spriteAtIndex(spritesheet, 0));
        pushQuad(160, 120, 160, 240, spriteAtIndex(spritesheet, 1));
        pushQuad(320, 120, 160, 240, spriteAtIndex(spritesheet, 2));
        pushQuad(480, 120, 160, 240, spriteAtIndex(spritesheet, 3));
        endRendering();
    }

    destroyTexture(texture0);
    destroyRenderer();
    destroyWindow();
}

