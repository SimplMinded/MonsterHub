#include "rendering/projection.h"

namespace monster_hub {

void orthogonalProjection(float* result,
        float left, float right,
        float bottom, float top,
        float near, float far)
{
    result[0] = 2 / (right - left);
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;

    result[4] = 0;
    result[5] = 2 / (top - bottom);
    result[6] = 0;
    result[7] = 0;
    
    result[8] = 0;
    result[9] = 0;
    result[10] = 2 / (near - far);
    result[11] = 0;

    result[12] = (left + right) / (left - right);
    result[13] = (bottom + top) / (bottom - top);
    result[14] = (near + far) / (near - far);
    result[15] = 1;
}

} // namespace monster_hub

