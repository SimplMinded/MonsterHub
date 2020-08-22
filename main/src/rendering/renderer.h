#pragma once

namespace monster_hub {

void initRenderer();
void destroyRenderer();

void setProjection(const float* projection);

void beginRendering();
void endRendering();

void pushQuad(float x, float y, float width, float height,
        float r, float g, float b, float a);

} // namespace monster_hub

