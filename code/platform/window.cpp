#include "window.hpp"

namespace engine
{
    void Window::create(const std::string& title, uint32_t width, uint32_t height)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::exit(EXIT_FAILURE);
        }

        _handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

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