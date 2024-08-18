#pragma once

#include "context.hpp"
#include "platform.hpp"
#include "window.hpp"

namespace engine::base
{
    class Factory
    {
    public:
        [[nodiscard]] virtual std::unique_ptr<Window>   create_window()   = 0;
        [[nodiscard]] virtual std::unique_ptr<Platform> create_platform() = 0;
        [[nodiscard]] virtual std::unique_ptr<Context>  create_context()  = 0;

        virtual ~Factory() = default;
    };
}