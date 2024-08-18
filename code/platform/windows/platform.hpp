#pragma once

#include "base/platform.hpp"

namespace engine::win32
{
    class Platform final : public base::Platform
    {
    public:
        static LRESULT process_events(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        void update() const override;
    };
}