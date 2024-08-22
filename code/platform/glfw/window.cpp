#include "window.hpp"
#include "window_events.hpp"

namespace engine::glfw
{
    void Window::create(const std::string& title)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::exit(EXIT_FAILURE);
        }
            _handle = glfwCreateWindow(_size.width, _size.height, title.c_str(), nullptr);
        if (_handle == nullptr)
        {
            std::exit(EXIT_FAILURE);
        }

        glfwSetWindowCloseCallback(_handle, WindowEvents::on_close);
    }

    void Window::destroy() const
    {
        glfwDestroyWindow(_handle);
        glfwTerminate();
    }

    void Window::display() const
    {
    }

    std::any Window::handle() const
    {
        return _handle;
    }
}