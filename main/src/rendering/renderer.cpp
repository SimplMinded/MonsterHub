#include "rendering/renderer.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <glad/glad.h>

#include "debug/assert.h"
#include "input.h"
#include "math/matrix.h"
#include "rendering/gl_assert.h"
#include "rendering/logger.h"
#include "rendering/texture.h"
#include "util/unreachable.h"
#include "window.h"

namespace monster_hub {

namespace {

struct Vertex
{
    float x, y;
    uint32_t textureIndex;
    float u, v;
    float r, g, b, a;
};

constexpr const char* vertex_shader_src =
    "#version 400 core\n"
    "\n"
    "layout(location=0) in vec4 in_position;\n"
    "layout(location=1) in uint in_textureIndex;\n"
    "layout(location=2) in vec2 in_texCoords;\n"
    "layout(location=3) in vec4 in_color;\n"
    "\n"
    "flat out uint vertTextureIndex;\n"
    "out vec2 vertTexCoords;\n"
    "out vec4 vertColor;\n"
    "\n"
    "uniform mat4 u_projection;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = u_projection * in_position;\n"
    "    vertTextureIndex = in_textureIndex;\n"
    "    vertTexCoords = in_texCoords;\n"
    "    vertColor = in_color;\n"
    "}\n";

constexpr const char* fragment_shader_src =
    "#version 400 core\n"
    "\n"
    "flat in uint vertTextureIndex;\n"
    "in vec2 vertTexCoords;\n"
    "in vec4 vertColor;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "uniform sampler2D[32] u_texture;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    if (vertTextureIndex != 0) {\n"
    "        fragColor = texture(u_texture[vertTextureIndex], vertTexCoords) * vertColor;\n"
    "    } else {\n"
    "        fragColor = vertColor;\n"
    "    }\n"
    "}\n";

uint32_t vao = 0;
uint32_t vbo = 0;
uint32_t ibo = 0;
uint32_t program = 0;

constexpr int32_t max_sprite_count = 10000;
Vertex vertices[max_sprite_count * 4] = {};
int32_t spriteCount = 0;

constexpr uint32_t max_texture_count = 32;
uint32_t textures[max_texture_count] = {};
uint32_t textureCount = 1;

void pushIndices()
{
    uint32_t indices[max_sprite_count * 6] = {};
    for (uint32_t i = 0; i < max_sprite_count; ++i)
    {
        indices[(i * 6) + 0] = (i * 4) + 0;
        indices[(i * 6) + 1] = (i * 4) + 1;
        indices[(i * 6) + 2] = (i * 4) + 2;
        
        indices[(i * 6) + 3] = (i * 4) + 0;
        indices[(i * 6) + 4] = (i * 4) + 2;
        indices[(i * 6) + 5] = (i * 4) + 3;
    }
    GL_ASSERT( glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &ibo) );
    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo) );
    GL_ASSERT( glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            max_sprite_count * 6, indices, GL_STATIC_DRAW) );
}

#if DEBUG_FEATURE_ENABLED(SHADER_VERIFICATION)

const char* shaderTypeToString(uint32_t type)
{
    switch (type)
    {
        case GL_VERTEX_SHADER:
            return "Vertex shader";
        case GL_FRAGMENT_SHADER:
            return "Fragment shader";
        default:
            unreachable("Unknown shader type");
    }
}

void verifyShaderCompilation(
        uint32_t    shader,
        uint32_t    type,
        const char* file,
        size_t      line)
{
    GLint status;
    GL_ASSERT( glGetShaderiv(shader, GL_COMPILE_STATUS, &status) );
    if (status != GL_TRUE)
    {
        int32_t length = 0;
        char message[1024];
        GL_ASSERT( glGetShaderInfoLog(shader, 1024, &length, message) );
        LOG_ERROR("%s::%lu: (%s) %s",
                file, line, shaderTypeToString(type), message);
        abort();
    }
}

#define VERIFY_SHADER_COMPILATION(shader, type) \
    verifyShaderCompilation(shader, type, __FILE__, __LINE__)

void verifyProgramLinking(uint32_t shaderProgram, const char* file, size_t line)
{
    GLint status;
    GL_ASSERT( glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status) );
    if (status != GL_TRUE)
    {
        int32_t length = 0;
        char message[1024];
        GL_ASSERT( glGetProgramInfoLog(shaderProgram, 1024, &length, message) );
        LOG_ERROR("%s::%lu: (Linker) %s", file, line, message);
        abort();
    }
}

#define VERIFY_PROGRAM_LINKING(program) \
    verifyProgramLinking(program, __FILE__, __LINE__)

#else

#define VERIFY_SHADER_COMPILATION(shader, type)
#define VERIFY_PROGRAM_LINKING(program)

#endif

uint32_t createShader(uint32_t type, const char* source)
{
    GL_ASSERT( uint32_t shader = glCreateShader(type) );
    GL_ASSERT( glShaderSource(shader, 1, &source, nullptr) );
    GL_ASSERT( glCompileShader(shader) );

    VERIFY_SHADER_COMPILATION(shader, type);

    return shader;
}

uint32_t createShaderProgram(uint32_t vertexShader, uint32_t fragmentShader)
{
    GL_ASSERT( uint32_t shaderProgram = glCreateProgram() );
    GL_ASSERT( glAttachShader(shaderProgram, vertexShader) );
    GL_ASSERT( glAttachShader(shaderProgram, fragmentShader) );
    GL_ASSERT( glLinkProgram(shaderProgram) );

    VERIFY_PROGRAM_LINKING(shaderProgram);

    return shaderProgram;
}

} // namespace

void initRenderer()
{
    GL_ASSERT( glGenVertexArrays(1, &vao) );
    GL_ASSERT( glBindVertexArray(vao) );

    GL_ASSERT( glGenBuffers(1, &vbo) );
    GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
    GL_ASSERT( glBufferData(GL_ARRAY_BUFFER,
            max_sprite_count * 4, nullptr, GL_DYNAMIC_DRAW) );

    GL_ASSERT( glEnableVertexAttribArray(0) );
    GL_ASSERT( glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, x))) );

    GL_ASSERT( glEnableVertexAttribArray(1) );
    GL_ASSERT( glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, textureIndex))) );

    GL_ASSERT( glEnableVertexAttribArray(2) );
    GL_ASSERT( glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, u))) );

    GL_ASSERT( glEnableVertexAttribArray(3) );
    GL_ASSERT( glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, r))) );

    pushIndices();

    GL_ASSERT( uint32_t vertexShader = createShader(
            GL_VERTEX_SHADER, vertex_shader_src) );
    GL_ASSERT( uint32_t fragmentShader = createShader(
            GL_FRAGMENT_SHADER, fragment_shader_src) );
    program = createShaderProgram(vertexShader, fragmentShader);
    GL_ASSERT( glDeleteShader(vertexShader) );
    GL_ASSERT( glDeleteShader(fragmentShader) );
    GL_ASSERT( glUseProgram(program) );

    GL_ASSERT( int32_t texturesLocation = glGetUniformLocation(
                program, "u_texture") );
    assert(texturesLocation != -1);
    int32_t samplers[32] = {};
    for (int32_t i = 0; i < 32; ++i) samplers[i] = i;
    GL_ASSERT( glUniform1iv(texturesLocation, 32, samplers) );
}

void destroyRenderer()
{
    GL_ASSERT( glDeleteProgram(program) );
    GL_ASSERT( glDeleteBuffers(1, &ibo) );
    GL_ASSERT( glDeleteBuffers(1, &vbo) );
    GL_ASSERT( glDeleteVertexArrays(1, &vao) );
}

void setProjection(const Matrix& projection)
{
    GL_ASSERT( int32_t location = glGetUniformLocation(program, "u_projection") );
    GL_ASSERT( glUniformMatrix4fv(location, 1, false, projection.elems) );
}

void beginRendering()
{
    GL_ASSERT( glClear(GL_COLOR_BUFFER_BIT) );
    spriteCount = 0;
    textureCount = 1;
}

void endRendering()
{
    for (uint32_t i = 1; i < textureCount; ++i)
    {
        GL_ASSERT( glActiveTexture(GL_TEXTURE0 + i) );
        GL_ASSERT( glBindTexture(GL_TEXTURE_2D, textures[i]) );
    }

    GL_ASSERT( glBufferSubData(GL_ARRAY_BUFFER,
            0,
            static_cast<uint32_t>(spriteCount * 4) * sizeof(Vertex),
            vertices) );
    GL_ASSERT( glDrawElements(GL_TRIANGLES, spriteCount * 6, GL_UNSIGNED_INT, 0) );

    swapBuffers();
    updateInput();
}

void pushQuad(float x, float y, float width, float height,
        const Texture& texture, float r, float g, float b, float a)
{
    assert(width > 0);
    assert(height > 0);
    assert(r >= 0 && r <= 1);
    assert(g >= 0 && g <= 1);
    assert(b >= 0 && b <= 1);
    assert(a >= 0 && a <= 1);
    assert(spriteCount < max_sprite_count);

    uint32_t textureIndex = 0;
    while (textureIndex < textureCount && textures[textureIndex] != texture.id)
    {
        textureIndex++;
    }
    assert(textureIndex < max_texture_count);
    if (textureIndex == textureCount)
    {
        textures[textureCount++] = texture.id;
    }

    vertices[(spriteCount * 4) + 0] =
        { x,         y,          textureIndex, 0, 0, r, g, b, a };
    vertices[(spriteCount * 4) + 1] =
        { x,         y + height, textureIndex, 0, 1, r, g, b, a };
    vertices[(spriteCount * 4) + 2] =
        { x + width, y + height, textureIndex, 1, 1, r, g, b, a };
    vertices[(spriteCount * 4) + 3] =
        { x + width, y,          textureIndex, 1, 0, r, g, b, a };
    spriteCount++;
}

void pushQuad(float x, float y, float width, float height,
        const Texture& texture)
{
    pushQuad(x, y, width, height, texture, 1, 1, 1, 1);
}

void pushQuad(float x, float y, float width, float height,
        float r, float g, float b, float a)
{
    pushQuad(x, y, width, height, {}, r, g, b, a);
}

} // namespace monster_hub

