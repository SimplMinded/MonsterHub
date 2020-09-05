#pragma once

#include <cstdint>

namespace monster_hub {

struct Texture;
struct TextureRegion;

struct Spritesheet
{
    uint32_t textureId;
    int32_t spriteCountX;
    int32_t spriteCountY;
};

Spritesheet makeSpritesheet(
        const Texture& texture, int32_t spriteSizeX, int32_t spriteSizeY);

Spritesheet makeSpritesheet(const Texture& texture, int32_t spriteSize);

int32_t spriteCount(const Spritesheet& spritesheet);

TextureRegion spriteAtIndex(const Spritesheet& spritesheet, int32_t index);

} // namespace monster_hub

