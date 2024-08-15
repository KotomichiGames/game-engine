#pragma once

#include "base/window.hpp"

namespace engine::glfw
{
    class Window final : public base::Window
    {
    public:
        void create(const std::string& title, int32_t width, int32_t height) override;
        void update()  const override;
        void destroy() const override;

        [[nodiscard]] bool is_closed() const override;

    private:
        GLFWwindow* _handle { };
    };
}