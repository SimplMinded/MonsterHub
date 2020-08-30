#pragma once

namespace monster_hub {

struct Matrix;

Matrix orthogonalProjection(
        float left, float right,
        float bottom, float top,
        float near, float far);

} // namespace monster_hub

