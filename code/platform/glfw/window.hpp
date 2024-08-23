#pragma once

#include "base/window.hpp"

namespace engine::glfw
{
    class Window final : public base::Window
    {
    public:
        void create()        override;
        void destroy() const override;
        void display() const override;

        [[nodiscard]] std::any handle() const override;

    private:
        GLFWwindow* _handle { };
    };
}