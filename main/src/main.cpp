#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

using namespace monster_hub;

int main()
{
    createWindow(640, 480, "Hello World");

    while (!isWindowClosed())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        swapBuffers();

        glfwPollEvents();
    }

    destroyWindow();
}

