#pragma once

#include <cstdint>

namespace monster_hub {

struct Texture;

struct TextureRegion
{
    uint32_t textureId;
    float u1;
    float v1;
    float u2;
    float v2;
};

TextureRegion makeTextureRegion(const Texture& texture,
        float u1, float v1, float u2, float v2);

TextureRegion makeTextureRegion(const Texture& texture);

} // namespace monster_hub

