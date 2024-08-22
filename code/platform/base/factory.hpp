#pragma once

#include "context.hpp"
#include "window.hpp"
#include "window_events.hpp"

namespace engine::base
{
    class Factory
    {
    public:
        [[nodiscard]] virtual std::unique_ptr<Context>      create_context() = 0;
        [[nodiscard]] virtual std::unique_ptr<Window>       create_window()  = 0;
        [[nodiscard]] virtual std::unique_ptr<WindowEvents> create_events()  = 0;

        virtual ~Factory() = default;
    };
}
