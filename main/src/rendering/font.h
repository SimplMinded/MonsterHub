#pragma once

#include <cstdint>

namespace monster_hub {

struct Spritesheet;

Spritesheet createBitmapFont(
        const char* name, int32_t glyphWidth, int32_t glyphHeight);

void destroyBitmapFont(Spritesheet& spritesheet);

} // namespace monster_hub

