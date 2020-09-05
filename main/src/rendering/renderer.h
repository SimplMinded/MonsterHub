#pragma once

namespace monster_hub {

struct Color;
struct Matrix;
struct TextureRegion;

void initRenderer();
void destroyRenderer();

void setProjection(const Matrix& projection);

void beginRendering();
void endRendering();

void pushQuad(float x, float y, float width, float height,
        const TextureRegion& textureRegion, const Color& color);

void pushQuad(float x, float y, float width, float height,
        const TextureRegion& textureRegion);

void pushQuad(float x, float y, float width, float height,
        const Color& color);

} // namespace monster_hub

