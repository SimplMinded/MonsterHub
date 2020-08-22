#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debug/assert.h"

namespace monster_hub {

namespace {

GLFWwindow* window = nullptr;

} // namespace

bool createWindow(int32_t width, int32_t height, const char* title)
{
    assert(window == nullptr);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwInit())
    {}

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr)
    {}

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {}

    return true;
}

void destroyWindow()
{
    assert(window != nullptr);
    glfwTerminate();
    window = nullptr;
}

bool isWindowClosed()
{
    assert(window != nullptr);
    return glfwWindowShouldClose(window);
}

void swapBuffers()
{
    assert(window != nullptr);
    glfwSwapBuffers(window);
}

} // namespace monster_hub

