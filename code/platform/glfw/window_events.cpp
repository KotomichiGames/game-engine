#include "window_events.hpp"
#include "window_manager.hpp"

namespace engine::glfw
{
    void WindowEvents::on_close()
    {
        WindowManager::instance().close();
    }

    void WindowEvents::update() const
    {
        glfwPollEvents();
    }
}