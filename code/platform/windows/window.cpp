#include "window.hpp"
#include "platform.hpp"

namespace engine::win32
{
    void Window::create(const std::string& title)
    {
        const HINSTANCE   instance = GetModuleHandle(nullptr);
        const WNDCLASSEX  window_class
        {
            .cbSize        = sizeof(WNDCLASSEX),
            .style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            .lpfnWndProc   = Platform::process_events,
            .hInstance     = instance,
            .hCursor       = LoadCursor(instance, IDC_ARROW),
            .lpszClassName = title.c_str(),
        };

        constexpr UINT extra = WS_EX_APPWINDOW;
        constexpr UINT style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;

        _class  = RegisterClassEx(&window_class);
        _handle = CreateWindowEx(extra, MAKEINTATOM(_class), title.c_str(), style, CW_USEDEFAULT, CW_USEDEFAULT,
                                                              _size.width, _size.height, nullptr, nullptr, instance, nullptr);
        ShowWindow(_handle, SW_SHOW);
    }

    void Window::destroy() const
    {
        DestroyWindow(_handle);

        UnregisterClass(MAKEINTATOM(_class), GetModuleHandle(nullptr));
    }

    std::any Window::handle() const
    {
        return _handle;
    }
}