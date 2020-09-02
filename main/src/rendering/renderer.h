#pragma once

namespace monster_hub {

struct Matrix;
struct Texture;

void initRenderer();
void destroyRenderer();

void setProjection(const Matrix& projection);

void beginRendering();
void endRendering();

void pushQuad(float x, float y, float width, float height,
        const Texture& texture, float r, float g, float b, float a);

void pushQuad(float x, float y, float width, float height,
        const Texture& texture);

void pushQuad(float x, float y, float width, float height,
        float r, float g, float b, float a);

} // namespace monster_hub

