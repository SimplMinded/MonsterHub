#pragma once

namespace monster_hub {

struct Image;

Image loadImage(const char* path);

void releaseImage(Image& image);

} // namespace monster_hub

