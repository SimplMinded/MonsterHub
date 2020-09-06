#pragma once

#include <cstdint>

namespace monster_hub {

struct Texture;
struct TextureRegion;

struct Spritesheet
{
    uint32_t textureId;
    int32_t textureWidth;
    int32_t textureHeight;
    int32_t spriteWidth;
    int32_t spriteHeight;
};

Spritesheet makeSpritesheet(
        const Texture& texture, int32_t spriteWidth, int32_t spriteHeight);

Spritesheet makeSpritesheet(const Texture& texture, int32_t spriteSize);

int32_t getspriteCountX(const Spritesheet& spritesheet);
int32_t getSpriteCountY(const Spritesheet& spritesheet);
int32_t getSpriteCount(const Spritesheet& spritesheet);

TextureRegion getSpriteAtIndex(const Spritesheet& spritesheet, int32_t index);

} // namespace monster_hub

