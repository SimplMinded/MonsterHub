#include <catch2/catch.hpp>

#include "math/vec2.h"

using namespace monster_hub;

SCENARIO("A vector has operators", "[vec2][math]")
{
    GIVEN("A vector")
    {
        Vec2 v = { 4, 9 };

        WHEN("The vector is negated")
        {
            Vec2 result = -v;

            THEN("The resulting vector has the negated components of the original vector")
            {
                CHECK(result.x == -4);
                CHECK(result.y == -9);
            }
        }

        WHEN("The vector is multiplied by a scalar")
        {
            Vec2 result = v * 3;

            THEN("The resulting vector has the components of the original vector multiplied by the scalar")
            {
                CHECK(result.x == 12);
                CHECK(result.y == 27);
            }
        }

        WHEN("the vector is divided by a scalar")
        {
            Vec2 result = v / 2;

            THEN("The resulting vector has the components of the original vector divided by the scalar")
            {
                CHECK(result.x == 2);
                CHECK(result.y == 4.5f);
            }
        }
    }

    GIVEN("2 different vectors")
    {
        Vec2 v1 = { 5, 3 };
        Vec2 v2 = { 1, 7 };

        WHEN("The vectors are added together")
        {
            Vec2 result = v1 + v2;

            THEN("The resulting vector are the component-wise sum of the added vectors")
            {
                CHECK(result.x == 6);
                CHECK(result.y == 10);
            }
        }

        WHEN("The vectors are subtracted from each other")
        {
            Vec2 result = v1 - v2;

            THEN("The resulting vector are the component-wise difference of the subtracted vectors")
            {
                CHECK(result.x == 4);
                CHECK(result.y == -4);
            }
        }
    }
}

