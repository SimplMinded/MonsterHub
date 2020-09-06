#include "rendering/font.h"

#include <cstdio>

#include <glad/glad.h>

#include "debug/assert.h"
#include "io/image.h"
#include "rendering/image.h"
#include "rendering/spritesheet.h"
#include "rendering/texture.h"

namespace monster_hub {

Spritesheet createBitmapFont(
        const char* name, int32_t glyphWidth, int32_t glyphHeight)
{
    assert(name != nullptr);

    char path[128] = {};
    snprintf(path, 128, "res/font/%s.png", name);

    Image image = loadImage(path);
    assert(glyphWidth > 0 && glyphWidth <= image.width);
    assert(glyphHeight > 0 && glyphHeight <= image.height);
    
    Texture texture = createTexture(image);
    releaseImage(image);

    return makeSpritesheet(texture, glyphWidth, glyphHeight);
}

void destroyBitmapFont(Spritesheet& spritesheet)
{
    assert(spritesheet.textureId != 0);
    assert(spritesheet.textureWidth > 0);
    assert(spritesheet.textureHeight > 0);
    assert(spritesheet.spriteWidth > 0 &&
            spritesheet.spriteWidth <= spritesheet.textureWidth);
    assert(spritesheet.spriteHeight > 0 &&
            spritesheet.spriteHeight <= spritesheet.textureHeight);

    glDeleteTextures(1, &spritesheet.textureId);

    spritesheet.textureId = 0;
    spritesheet.textureWidth = 0;
    spritesheet.textureHeight = 0;
    spritesheet.spriteWidth = 0;
    spritesheet.spriteHeight = 0;
}

} // namespace monster_hub

