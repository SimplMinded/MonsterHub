#pragma once

#include <cstdint>

namespace monster_hub {

bool createWindow(int32_t width, int32_t height, const char* title);
void destroyWindow();

bool isWindowClosed();

void swapBuffers();

} // namespace monster_hub

