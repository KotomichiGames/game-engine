#pragma once

#include "base/platform.hpp"

namespace engine::win32
{
    class Platform final : public base::Platform
    {
    public:
        void update() const override;
    };
}