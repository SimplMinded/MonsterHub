#pragma once

#include "key.h"

namespace monster_hub {

void updateInput();

bool isKeyDown(Key key);
bool isKeyUp(Key key);
bool isKeyPressed(Key key);
bool isKeyReleased(Key key);

void getCursorPos(float& x, float& y);

bool isMouseButtonDown(Button button);
bool isMouseButtonUp(Button button);
bool isMouseButtonPressed(Button button);
bool isMouseButtonReleased(Button button);

} // namespace monster_hub

