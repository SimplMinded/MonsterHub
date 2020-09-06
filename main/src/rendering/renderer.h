#pragma once

namespace monster_hub {

struct Color;
struct Matrix;
struct Spritesheet;
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

void pushText(float x, float y, float lineHeight,
        const char* text, const Spritesheet& font, const Color& color);

void pushText(float x, float y, float lineHeight,
        const char* text, const Spritesheet& font);

} // namespace monster_hub

