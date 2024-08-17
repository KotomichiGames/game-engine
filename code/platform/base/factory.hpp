#pragma once

#include "platform.hpp"
#include "window.hpp"

namespace engine::base
{
    class Factory
    {
    public:
        virtual std::unique_ptr<Window>   create_window()   = 0;
        virtual std::unique_ptr<Platform> create_platform() = 0;

        virtual ~Factory() = default;
    };
}