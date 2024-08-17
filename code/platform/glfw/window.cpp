#include "window.hpp"
#include "platform.hpp"

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

        glfwSetWindowCloseCallback(_handle, Platform::on_close_event);

        glfwMakeContextCurrent(_handle);
    }

    void Window::update() const
    {
        glfwSwapBuffers(_handle);
    }

    void Window::destroy() const
    {
        glfwDestroyWindow(_handle);
        glfwTerminate();
    }

    std::any Window::handle() const
    {
        return _handle;
    }
}