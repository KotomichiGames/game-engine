#pragma once

#include "base/window.hpp"

namespace engine::win32
{
    class Window final : public base::Window
    {
    public:
        void create(const std::string& title) override;
        void destroy()                  const override;

        [[nodiscard]] std::any handle() const override;

    private:
        HWND _handle { };
        ATOM _class  { };
    };
}