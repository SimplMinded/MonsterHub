#include "rendering/renderer.h"

#include <cstdint>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debug/assert.h"
#include "rendering/logger.h"
#include "util/unreachable.h"
#include "window.h"

namespace monster_hub {

namespace {

#if DEBUG_FEATURE_ENABLED(GL_ASSERT)

const char* glErrorToString(GLenum error)
{
    switch (error)
    {
        case GL_NO_ERROR:
            return "No error";
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "Invalid framebuffer operation";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
        case GL_STACK_UNDERFLOW:
            return "Stack underflow";
        case GL_STACK_OVERFLOW:
            return "Stack overflow";
        default:
            unreachable("Unknown OpenGL error");
    }
}

void glAssert_impl(const char* file, size_t line, const char* call)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_ERROR("%s::%lu: %s ( %s )",
                file, line, glErrorToString(error), call);
        abort();
    }
}

#define GL_ASSERT(call) \
    while (glGetError() != GL_NO_ERROR); \
    call; \
    glAssert_impl(__FILE__, __LINE__, #call)

#else

#define GL_ASSERT(call) call

#endif

struct Vertex
{
    float x, y;
    float r, g, b, a;
};

constexpr const char* vertex_shader_src =
    "#version 400 core\n"
    "\n"
    "layout(location=0) in vec4 in_position;\n"
    "layout(location=1) in vec4 in_color;\n"
    "\n"
    "out vec4 vertColor;\n"
    "\n"
    "uniform mat4 u_projection;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = u_projection * in_position;\n"
    "    vertColor = in_color;\n"
    "}\n";

constexpr const char* fragment_shader_src =
    "#version 400 core\n"
    "\n"
    "in vec4 vertColor;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    fragColor = vertColor;\n"
    "}\n";

uint32_t vao = 0;
uint32_t vbo = 0;
uint32_t ibo = 0;
uint32_t program = 0;

constexpr int32_t max_sprite_count = 10000;
Vertex vertices[max_sprite_count * 4] = {};
int32_t spriteCount = 0;

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
    GL_ASSERT( glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex),
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
}

void destroyRenderer()
{
    GL_ASSERT( glDeleteProgram(program) );
    GL_ASSERT( glDeleteBuffers(1, &ibo) );
    GL_ASSERT( glDeleteBuffers(1, &vbo) );
    GL_ASSERT( glDeleteVertexArrays(1, &vao) );
}

void setProjection(const float* projection)
{
    GL_ASSERT( int32_t location = glGetUniformLocation(program, "u_projection") );
    GL_ASSERT( glUniformMatrix4fv(location, 1, false, projection) );
}

void beginRendering()
{
    GL_ASSERT( glClear(GL_COLOR_BUFFER_BIT) );
    spriteCount = 0;
}

void endRendering()
{
    GL_ASSERT( glBufferSubData(GL_ARRAY_BUFFER,
            0, static_cast<uint32_t>(spriteCount * 4) * sizeof(Vertex), vertices) );
    GL_ASSERT( glDrawElements(GL_TRIANGLES, spriteCount * 6, GL_UNSIGNED_INT, 0) );

    swapBuffers();
    glfwPollEvents();
}

void pushQuad(float x, float y, float width, float height,
        float r, float g, float b, float a)
{
    assert(spriteCount < max_sprite_count);

    vertices[spriteCount + 0] = { x,         y,          r, g, b, a };
    vertices[spriteCount + 1] = { x,         y + height, r, g, b, a };
    vertices[spriteCount + 2] = { x + width, y + height, r, g, b, a };
    vertices[spriteCount + 3] = { x + width, y,          r, g, b, a };
    spriteCount++;
}

} // namespace monster_hub

