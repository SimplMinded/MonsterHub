#pragma once

#include <cstdint>

namespace monster_hub {

struct Image
{
    int32_t width;
    int32_t height;
    uint8_t* data;
};

Image makeImage(int32_t width, int32_t height, uint8_t* data);

} // namespace monster_hub

