#include "platform.hpp"
#include "window_instance.hpp"

namespace engine::win32
{
    LRESULT Platform::process_events(const HWND hwnd, const UINT msg, const WPARAM wparam, const LPARAM lparam)
    {
        switch (msg)
        {
            case WM_CLOSE:
            {
                WindowInstance::instance().close();
                return 0;
            }
        }

        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    void Platform::update() const
    {
        MSG msg;

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                WindowInstance::instance().close();
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
}