#include "rendering/spritesheet.h"

#include "rendering/texture.h"
#include "rendering/texture_region.h"

namespace monster_hub {

Spritesheet makeSpritesheet(
        const Texture& texture, int32_t spriteSizeX, int32_t spriteSizeY)
{
    return {
        texture.id,
        texture.width / spriteSizeX,
        texture.height / spriteSizeY
    };
}

Spritesheet makeSpritesheet(const Texture& texture, int32_t spriteSize)
{
    return makeSpritesheet(texture, spriteSize, spriteSize);
}

int32_t spriteCount(const Spritesheet& spritesheet)
{
    return spritesheet.spriteCountX * spritesheet.spriteCountY;
}

TextureRegion spriteAtIndex(const Spritesheet& spritesheet, int32_t index)
{
    const int32_t xIndex = index % spritesheet.spriteCountX;
    const int32_t yIndex = index / spritesheet.spriteCountX;

    return {
        spritesheet.textureId,
        static_cast<float>(xIndex) / static_cast<float>(spritesheet.spriteCountX),
        static_cast<float>(yIndex) / static_cast<float>(spritesheet.spriteCountY),
        static_cast<float>(xIndex + 1) /
            static_cast<float>(spritesheet.spriteCountX),
        static_cast<float>(yIndex + 1) /
            static_cast<float>(spritesheet.spriteCountY)
    };
}

} // namespace monster_hub

