#include "window.hpp"
#include "window_events.hpp"

namespace engine::win32
{
    void Window::register_window_class()
    {
        const WNDCLASSEX   wndclassex
        {
            .cbSize        = sizeof(WNDCLASSEX),
            .style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            .lpfnWndProc   = WindowEvents::process,
            .hInstance     = GetModuleHandle(nullptr),
            .hCursor       = LoadCursor(nullptr, IDC_ARROW),
            .lpszClassName = "KotomichiGames",
        };

        _wndclass = RegisterClassEx(&wndclassex);
    }

    void Window::create(const std::string& title)
    {
        register_window_class();

        constexpr UINT extra = WS_EX_APPWINDOW;
        constexpr UINT style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;

        _handle = CreateWindowEx(extra, MAKEINTATOM(_wndclass), title.c_str(), style, CW_USEDEFAULT, CW_USEDEFAULT, _size.width, _size.height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    }

    void Window::destroy() const
    {
        DestroyWindow(_handle);

        unregister_windows_class();
    }

    void Window::unregister_windows_class() const
    {
        if (_wndclass)
        {
            UnregisterClass(MAKEINTATOM(_wndclass), GetModuleHandle(nullptr));
        }
    }

    void Window::display() const
    {
        ShowWindow(_handle, SW_SHOW);
    }

    std::any Window::handle() const
    {
        return _handle;
    }
}