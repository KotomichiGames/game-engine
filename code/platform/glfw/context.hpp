#pragma once

#include "base/context.hpp"

namespace engine::glfw
{
    class Context final : public base::Context
    {
    public:
        void create(std::any window_handle) override;
        void destroy()                      override;
        void update()                       override;
    };
}