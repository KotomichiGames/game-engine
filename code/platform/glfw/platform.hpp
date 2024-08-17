#pragma once

#include "base/platform.hpp"

namespace engine::glfw
{
    class Platform final : public base::Platform
    {
    public:
        static void close_callback();

        void update() const override;
    };
}