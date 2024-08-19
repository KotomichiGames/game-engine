#pragma once

#include "base/context.hpp"

namespace engine::glfw
{
    class Context final : public base::Context
    {
    public:
        void create(std::any handle) override;
        void update()                override;
        void destroy()               override;

    private:
        GLFWwindow* _handle { };
    };
}