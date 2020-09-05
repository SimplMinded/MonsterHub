#include "io/image.h"

#include <cstdint>

#include <stb_image.h>

#include "debug/assert.h"
#include "rendering/image.h"

namespace monster_hub {

Image loadImage(const char* path)
{
    assert(path != nullptr);

    int32_t width;
    int32_t height;
    int32_t channelCount;
    uint8_t* data = stbi_load(path, &width, &height, &channelCount, 4);

    return makeImage(width, height, data);
}

void releaseImage(Image& image)
{
    assert(image.width > 0);
    assert(image.height > 0);
    assert(image.data != nullptr);

    stbi_image_free(image.data);

    image.width = 0;
    image.height = 0;
    image.data = nullptr;
}

} // namespace monster_hub

