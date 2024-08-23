#pragma once

#include "base/window_events.hpp"

namespace engine::win32
{
    class WindowEvents final : public base::WindowEvents
    {
    public:
        static LRESULT process(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        void update()  const override;
    };
}