#pragma once

#include "base/window.hpp"

namespace engine::glfw
{
    class Window final : public base::Window
    {
    public:
        void create(const std::string& title) override;
        void update()  const override;
        void destroy() const override;

        [[nodiscard]] std::any handle() const override;

    private:
        GLFWwindow* _handle { };
    };
}