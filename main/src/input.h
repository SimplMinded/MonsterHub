#pragma once

#include "key.h"

namespace monster_hub {

void updateInput();

bool isKeyDown(Key key);
bool isKeyUp(Key key);
bool isKeyPressed(Key key);
bool isKeyReleased(Key key);

} // namespace monster_hub

