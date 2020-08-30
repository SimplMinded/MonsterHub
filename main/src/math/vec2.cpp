#include "math/vec2.h"

#include "debug/assert.h"

namespace monster_hub {

Vec2 operator -(const Vec2& vec)
{
    return { -vec.x, -vec.y };
}

Vec2 operator +(const Vec2& lhs, const Vec2& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Vec2 operator -(const Vec2& lhs, const Vec2& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Vec2 operator *(const Vec2& lhs, float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs };
}

Vec2 operator *(float lhs, const Vec2& rhs)
{
    return rhs * lhs;
}

Vec2 operator /(const Vec2& lhs, float rhs)
{
    assert(rhs != 0);

    return { lhs.x / rhs, lhs.y / rhs };
}

} // namespace monster_hub

