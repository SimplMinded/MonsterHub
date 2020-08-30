#include "rendering/projection.h"

#include "math/matrix.h"

namespace monster_hub {

Matrix orthogonalProjection(
        float left, float right,
        float bottom, float top,
        float near, float far)
{
    return {
        2 / (right - left),              0,                               0,                           0,
        0,                               2 / (top - bottom),              0,                           0,
        0,                               0,                               2 / (near - far),            0,
        (left + right) / (left - right), (bottom + top) / (bottom - top), (near + far) / (near - far), 1
    };
}

} // namespace monster_hub

