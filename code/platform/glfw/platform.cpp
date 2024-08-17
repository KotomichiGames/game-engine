#include "platform.hpp"
#include "window_instance.hpp"

namespace engine::glfw
{
    void Platform::on_close_event()
    {
        WindowInstance::instance().close();
    }

    void Platform::update() const
    {
        glfwPollEvents();
    }
}