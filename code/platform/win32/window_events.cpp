#include "window_events.hpp"
#include "core/window_manager.hpp"

namespace engine::win32
{
    LRESULT WindowEvents::process(const HWND hwnd, const UINT msg, const WPARAM wparam, const LPARAM lparam)
    {
        switch (msg)
        {
            case WM_CLOSE:
            {
                core::WindowManager::instance().close();
                return 0;
            }
        }

        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    void WindowEvents::update() const
    {
        MSG msg;

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                core::WindowManager::instance().close();
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
}