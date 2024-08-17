#pragma once

#include "base/platform.hpp"

namespace engine::glfw
{
    class Platform final : public base::Platform
    {
    public:
        void update() const override;
    };
}