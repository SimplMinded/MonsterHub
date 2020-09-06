#pragma once

#include <cstdint>

namespace monster_hub {

struct Image;

struct Texture
{
    int32_t width = 0;
    int32_t height = 0;
    uint32_t id = 0;
};

Texture createTexture(int32_t width, int32_t height, uint8_t* pixels);
Texture createTexture(const Image& image);

void destroyTexture(Texture& texture);

} // namespace monster_hub

