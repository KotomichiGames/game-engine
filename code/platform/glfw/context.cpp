#include "context.hpp"

namespace engine::glfw
{
    void Context::create(const std::any handle)
    {
                               _handle = std::any_cast<GLFWwindow*>(handle);
        glfwMakeContextCurrent(_handle);
    }

    void Context::update()
    {
        glfwSwapBuffers(_handle);
    }

    void Context::destroy()
    {
    }
}