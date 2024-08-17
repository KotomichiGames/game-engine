#include "platform.hpp"
#include "window_instance.hpp"

namespace engine::glfw
{
    void Platform::close_callback()
    {
        WindowInstance::instance().close();
    }

    void Platform::update() const
    {
        glfwPollEvents();
    }
}