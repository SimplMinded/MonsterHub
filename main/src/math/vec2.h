#pragma once

namespace monster_hub {

struct Vec2
{
    float x = 0;
    float y = 0;
};

Vec2 operator -(const Vec2& vec);
Vec2 operator +(const Vec2& lhs, const Vec2& rhs);
Vec2 operator -(const Vec2& lhs, const Vec2& rhs);
Vec2 operator *(const Vec2& lhs, float rhs);
Vec2 operator *(float lhs, const Vec2& rhs);
Vec2 operator /(const Vec2& lhs, float rhs);

} // namespace monster_hub

