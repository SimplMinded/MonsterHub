#include "rendering/color.h"

namespace monster_hub {

Color makeColor(float r, float g, float b, float a)
{
    return { r, g, b, a };
}

Color makeColor(float r, float g, float b)
{
    return makeColor(r, g, b, 1);
}

} // namespace monster_hub

