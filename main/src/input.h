#pragma once

#include "key.h"

namespace monster_hub {

struct Vec2;

void updateInput();

bool isKeyDown(Key key);
bool isKeyUp(Key key);
bool isKeyPressed(Key key);
bool isKeyReleased(Key key);

Vec2 getCursorPos();

bool isMouseButtonDown(Button button);
bool isMouseButtonUp(Button button);
bool isMouseButtonPressed(Button button);
bool isMouseButtonReleased(Button button);

} // namespace monster_hub

