#pragma once

namespace monster_hub {

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

Color makeColor(float r, float g, float b, float a);
Color makeColor(float r, float g, float b);

} // namespace monster_hub

