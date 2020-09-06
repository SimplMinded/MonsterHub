#include "rendering/spritesheet.h"

#include "rendering/texture.h"
#include "rendering/texture_region.h"

namespace monster_hub {

Spritesheet makeSpritesheet(
        const Texture& texture, int32_t spriteWidth, int32_t spriteHeight)
{
    return {
        texture.id,
        texture.width,
        texture.height,
        spriteWidth,
        spriteHeight
    };
}

Spritesheet makeSpritesheet(const Texture& texture, int32_t spriteSize)
{
    return makeSpritesheet(texture, spriteSize, spriteSize);
}

int32_t getSpriteCountX(const Spritesheet& spritesheet)
{
    return spritesheet.textureWidth / spritesheet.spriteWidth;
}

int32_t getSpriteCountY(const Spritesheet& spritesheet)
{
    return spritesheet.textureHeight / spritesheet.spriteHeight;
}

int32_t getSpriteCount(const Spritesheet& spritesheet)
{
    return getSpriteCountX(spritesheet) * getSpriteCountY(spritesheet);
}

TextureRegion getSpriteAtIndex(const Spritesheet& spritesheet, int32_t index)
{
    const int32_t xIndex = index % getSpriteCountX(spritesheet);
    const int32_t yIndex = index / getSpriteCountX(spritesheet);

    return {
        spritesheet.textureId,
        static_cast<float>(xIndex * spritesheet.spriteWidth) / 
            static_cast<float>(spritesheet.textureWidth),
        1 - (static_cast<float>((yIndex + 1) * spritesheet.spriteHeight) /
            static_cast<float>(spritesheet.textureHeight)),
        static_cast<float>((xIndex + 1) * spritesheet.spriteWidth) /
            static_cast<float>(spritesheet.textureWidth),
        1 - (static_cast<float>(yIndex * spritesheet.spriteHeight) /
            static_cast<float>(spritesheet.textureHeight))
    };
}

} // namespace monster_hub

