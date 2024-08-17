#include "platform.hpp"

namespace engine::glfw
{
    void Platform::update() const
    {
        glfwPollEvents();
    }
}