#include "input.h"
#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debug/assert.h"
#include "math/vec2.h"
#include "util/unreachable.h"

namespace monster_hub {

// window.h

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

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

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

// input.h

namespace {

int toGlfwKey(uint32_t key)
{
    switch (key)
    {
        case KEY_SPACE:
            return GLFW_KEY_SPACE;
        case KEY_APOSTROPHE:
            return GLFW_KEY_APOSTROPHE;
        case KEY_COMMA:
            return GLFW_KEY_COMMA;
        case KEY_MINUS:
            return GLFW_KEY_MINUS;
        case KEY_PERIOD:
            return GLFW_KEY_PERIOD;
        case KEY_SLASH:
            return GLFW_KEY_SLASH;
        case KEY_0:
            return GLFW_KEY_0;
        case KEY_1:
            return GLFW_KEY_1;
        case KEY_2:
            return GLFW_KEY_2;
        case KEY_3:
            return GLFW_KEY_3;
        case KEY_4:
            return GLFW_KEY_4;
        case KEY_5:
            return GLFW_KEY_5;
        case KEY_6:
            return GLFW_KEY_6;
        case KEY_7:
            return GLFW_KEY_7;
        case KEY_8:
            return GLFW_KEY_8;
        case KEY_9:
            return GLFW_KEY_9;
        case KEY_SEMICOLON:
            return GLFW_KEY_SEMICOLON;
        case KEY_EQUAL:
            return GLFW_KEY_EQUAL;
        case KEY_A:
            return GLFW_KEY_A;
        case KEY_B:
            return GLFW_KEY_B;
        case KEY_C:
            return GLFW_KEY_C;
        case KEY_D:
            return GLFW_KEY_D;
        case KEY_E:
            return GLFW_KEY_E;
        case KEY_F:
            return GLFW_KEY_F;
        case KEY_G:
            return GLFW_KEY_G;
        case KEY_H:
            return GLFW_KEY_H;
        case KEY_I:
            return GLFW_KEY_I;
        case KEY_J:
            return GLFW_KEY_J;
        case KEY_K:
            return GLFW_KEY_K;
        case KEY_L:
            return GLFW_KEY_L;
        case KEY_M:
            return GLFW_KEY_M;
        case KEY_N:
            return GLFW_KEY_N;
        case KEY_O:
            return GLFW_KEY_O;
        case KEY_P:
            return GLFW_KEY_P;
        case KEY_Q:
            return GLFW_KEY_Q;
        case KEY_R:
            return GLFW_KEY_R;
        case KEY_S:
            return GLFW_KEY_S;
        case KEY_T:
            return GLFW_KEY_T;
        case KEY_U:
            return GLFW_KEY_U;
        case KEY_V:
            return GLFW_KEY_V;
        case KEY_W:
            return GLFW_KEY_W;
        case KEY_X:
            return GLFW_KEY_X;
        case KEY_Y:
            return GLFW_KEY_Y;
        case KEY_Z:
            return GLFW_KEY_Z;
        case KEY_LEFT_BRACKET:
            return GLFW_KEY_LEFT_BRACKET;
        case KEY_BACKSLASH:
                return GLFW_KEY_BACKSLASH;
        case KEY_RIGHT_BRACKET:
                return GLFW_KEY_RIGHT_BRACKET;
        case KEY_GRAVE_ACCENT:
                return GLFW_KEY_GRAVE_ACCENT;
        case KEY_ESCAPE:
                return GLFW_KEY_ESCAPE;
        case KEY_ENTER:
                return GLFW_KEY_ENTER;
        case KEY_TAB:
                return GLFW_KEY_TAB;
        case KEY_BACKSPACE:
                return GLFW_KEY_BACKSPACE;
        case KEY_INSERT:
                return GLFW_KEY_INSERT;
        case KEY_DELETE:
                return GLFW_KEY_DELETE;
        case KEY_RIGHT:
                return GLFW_KEY_RIGHT;
        case KEY_LEFT:
                return GLFW_KEY_LEFT;
        case KEY_DOWN:
                return GLFW_KEY_DOWN;
        case KEY_UP:
                return GLFW_KEY_UP;
        case KEY_PAGE_UP:
                return GLFW_KEY_PAGE_UP;
        case KEY_PAGE_DOWN:
                return GLFW_KEY_PAGE_DOWN;
        case KEY_HOME:
                return GLFW_KEY_HOME;
        case KEY_END:
                return GLFW_KEY_END;
        case KEY_CAPS_LOCK:
                return GLFW_KEY_CAPS_LOCK;
        case KEY_SCROLL_LOCK:
                return GLFW_KEY_SCROLL_LOCK;
        case KEY_NUM_LOCK:
                return GLFW_KEY_NUM_LOCK;
        case KEY_PRINT_SCREEN:
                return GLFW_KEY_PRINT_SCREEN;
        case KEY_F1:
                return GLFW_KEY_F1;
        case KEY_F2:
                return GLFW_KEY_F2;
        case KEY_F3:
                return GLFW_KEY_F3;
        case KEY_F4:
                return GLFW_KEY_F4;
        case KEY_F5:
                return GLFW_KEY_F5;
        case KEY_F6:
                return GLFW_KEY_F6;
        case KEY_F7:
                return GLFW_KEY_F7;
        case KEY_F8:
                return GLFW_KEY_F8;
        case KEY_F9:
                return GLFW_KEY_F9;
        case KEY_F10:
                return GLFW_KEY_F10;
        case KEY_F11:
                return GLFW_KEY_F11;
        case KEY_F12:
                return GLFW_KEY_F12;
        case KEY_NP_0:
                return GLFW_KEY_KP_0;
        case KEY_NP_1:
                return GLFW_KEY_KP_1;
        case KEY_NP_2:
                return GLFW_KEY_KP_2;
        case KEY_NP_3:
                return GLFW_KEY_KP_3;
        case KEY_NP_4:
                return GLFW_KEY_KP_4;
        case KEY_NP_5:
                return GLFW_KEY_KP_5;
        case KEY_NP_6:
                return GLFW_KEY_KP_6;
        case KEY_NP_7:
                return GLFW_KEY_KP_7;
        case KEY_NP_8:
                return GLFW_KEY_KP_8;
        case KEY_NP_9:
                return GLFW_KEY_KP_9;
        case KEY_NP_DECIMAL:
                return GLFW_KEY_KP_DECIMAL;
        case KEY_NP_DIVIDE:
                return GLFW_KEY_KP_DIVIDE;
        case KEY_NP_MULTIPLY:
                return GLFW_KEY_KP_MULTIPLY;
        case KEY_NP_SUBTRACT:
                return GLFW_KEY_KP_SUBTRACT;
        case KEY_NP_ADD:
                return GLFW_KEY_KP_ADD;
        case KEY_NP_ENTER:
                return GLFW_KEY_KP_ENTER;
        case KEY_NP_EQUAL:
                return GLFW_KEY_KP_EQUAL;
        case KEY_LEFT_SHIFT:
                return GLFW_KEY_LEFT_SHIFT;
        case KEY_LEFT_CONTROL:
                return GLFW_KEY_LEFT_CONTROL;
        case KEY_LEFT_ALT:
                return GLFW_KEY_LEFT_ALT;
        case KEY_LEFT_SUPER:
                return GLFW_KEY_LEFT_SUPER;
        case KEY_RIGHT_SHIFT:
                return GLFW_KEY_RIGHT_SHIFT;
        case KEY_RIGHT_CONTROL:
                return GLFW_KEY_RIGHT_CONTROL;
        case KEY_RIGHT_ALT:
                return GLFW_KEY_RIGHT_ALT;
        case KEY_RIGHT_SUPER:
                return GLFW_KEY_RIGHT_SUPER;
        default:
                unreachable("Unknown key");
    }
}

int toGlfwButton(uint32_t button)
{
    switch (button)
    {
        case BUTTON_LEFT:
            return GLFW_MOUSE_BUTTON_LEFT;
        case BUTTON_RIGHT:
            return GLFW_MOUSE_BUTTON_RIGHT;
        case BUTTON_MIDDLE:
            return GLFW_MOUSE_BUTTON_MIDDLE;
        default:
            unreachable("Unknown button");
    }
}

constexpr uint8_t current_state_bit = (1 << 0);
constexpr uint8_t previous_state_bit = (1 << 1);

uint8_t keyState[KEY_COUNT] = {};
uint8_t buttonState[BUTTON_COUNT] = {};

} // namespace

void updateInput()
{
    assert(window != nullptr);

    glfwPollEvents();
    for (uint32_t i = 0; i < KEY_COUNT; ++i)
    {
        keyState[i] = ((keyState[i] << 1) & previous_state_bit);
        keyState[i] |= static_cast<uint8_t>(
                glfwGetKey(window, toGlfwKey(i)) == GLFW_PRESS);
    }
    for (uint32_t i = 0; i < BUTTON_COUNT; ++i)
    {
        buttonState[i] = ((buttonState[i] << 1) & previous_state_bit);
        buttonState[i] |= static_cast<uint8_t>(
                glfwGetMouseButton(window, toGlfwButton(i)) == GLFW_PRESS);
    }
}

bool isKeyDown(Key key)
{
    assert(key != KEY_COUNT);

    return keyState[key] & current_state_bit;
}

bool isKeyUp(Key key)
{
    assert(key != KEY_COUNT);

    return !isKeyDown(key);
}

bool isKeyPressed(Key key)
{
    assert(key != KEY_COUNT);

    return isKeyDown(key) && !(keyState[key] & previous_state_bit);
}

bool isKeyReleased(Key key)
{
    assert(key != KEY_COUNT);

    return isKeyUp(key) && (keyState[key] & previous_state_bit);
}

Vec2 getCursorPos()
{
    assert(window != nullptr);

    double posX, posY;
    glfwGetCursorPos(window, &posX, &posY);

    return { static_cast<float>(posX), static_cast<float>(posY) };
}

bool isMouseButtonDown(Button button)
{
    assert(button != BUTTON_COUNT);

    return buttonState[button] & current_state_bit;
}

bool isMouseButtonUp(Button button)
{
    assert(button != BUTTON_COUNT);

    return !isMouseButtonDown(button);
}

bool isMouseButtonPressed(Button button)
{
    assert(button != BUTTON_COUNT);

    return isMouseButtonDown(button) &&
        !(buttonState[button] & previous_state_bit);
}

bool isMouseButtonReleased(Button button)
{
    assert(button != BUTTON_COUNT);

    return isMouseButtonUp(button) && 
        (buttonState[button] & previous_state_bit);
}

} // namespace monster_hub

