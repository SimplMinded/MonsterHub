#include "texture.h"

#include <glad/glad.h>

#include "debug/assert.h"
#include "rendering/gl_assert.h"

namespace monster_hub {

Texture createTexture(int32_t width, int32_t height, uint8_t* pixels)
{
    assert(width > 0);
    assert(height > 0);
    assert(pixels != nullptr);

    uint32_t textureId = 0;
    GL_ASSERT( glGenTextures(1, &textureId) );
    GL_ASSERT( glBindTexture(GL_TEXTURE_2D, textureId) );

    GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST) );
    GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST) );

    GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
    GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );

    GL_ASSERT( glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            pixels) );

    return { width, height, textureId };
}

void destroyTexture(Texture& texture)
{
    assert(texture.id != 0);

    GL_ASSERT( glDeleteTextures(1, &texture.id) );

    texture.width = 0;
    texture.height = 0;
    texture.id = 0;
}

} // namespace monster_hub

