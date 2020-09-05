#include "rendering/texture_region.h"

#include "debug/assert.h"
#include "rendering/texture.h"

namespace monster_hub {

TextureRegion makeTextureRegion(const Texture& texture,
        float u1, float v1, float u2, float v2)
{
    assert(texture.width > 0);
    assert(texture.height > 0);
    assert(texture.id != 0);
    assert(u1 >= 0 && u1 <= 1);
    assert(v1 >= 0 && v1 <= 1);
    assert(u2 >= 0 && u2 <= 1);
    assert(v2 >= 0 && v2 <= 1);

    return { texture.id, u1, v1, u2, v2 };
}

TextureRegion makeTextureRegion(const Texture& texture)
{
    return makeTextureRegion(texture, 0, 0, 1, 1);
}

} // namespace monster_hub

