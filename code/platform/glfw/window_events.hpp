#pragma once

#include "base/window_events.hpp"

namespace engine::glfw
{
    class WindowEvents final : public base::WindowEvents
    {
    public:
        static void on_close();

        void update() const override;
    };
}