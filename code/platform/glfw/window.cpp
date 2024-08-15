#include "window.hpp"

namespace engine::glfw
{
    void Window::create(const std::string& title, const int32_t width, const int32_t height)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::exit(EXIT_FAILURE);
        }

        _handle = glfwCreateWindow(width, height, title.c_str(), nullptr);

        if (_handle == nullptr)
        {
            std::exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(_handle);
    }

    void Window::update() const
    {
        glfwSwapBuffers(_handle);
        glfwPollEvents();
    }

    void Window::destroy() const
    {
        glfwDestroyWindow(_handle);
        glfwTerminate();
    }

    bool Window::is_closed() const
    {
        return glfwWindowShouldClose(_handle) == GLFW_TRUE;
    }
}