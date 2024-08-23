#pragma once

#include "base/window.hpp"

namespace engine::win32
{
    class Window final : public base::Window
    {
    public:
        void create()        override;
        void destroy() const override;
        void display() const override;

        [[nodiscard]] std::any handle() const override;

    private:
        void    register_window_class();
        void unregister_windows_class() const;

        ATOM _wndclass { };
        HWND _handle   { };
    };
}