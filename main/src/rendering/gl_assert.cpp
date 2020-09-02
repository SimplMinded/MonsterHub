#include "rendering/gl_assert.h"

#include <cstdio>
#include <cstdlib>

#include <glad/glad.h>

#include "io/terminal.h"
#include "util/unreachable.h"

namespace monster_hub {

namespace {

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

} // namespace

void glAssert_impl(const char* file, size_t line, const char* call)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        char buffer[256] = {};
        snprintf(buffer, 256, "%s::%lu: %s ( %s )\n",
                file, line, glErrorToString(error), call);
        printToTerminal(buffer);

        abort();
    }
}

} // namespace monster_hub

