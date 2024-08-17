#pragma once

#include "base/platform.hpp"

namespace engine::glfw
{
    class Platform final : public base::Platform
    {
    public:
        static void on_close_event();

        void update() const override;
    };
}