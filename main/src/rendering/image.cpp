#include "rendering/image.h"

namespace monster_hub {

Image makeImage(int32_t width, int32_t height, uint8_t* data)
{
    return { width, height, data };
}

} // namespace monster_hub

