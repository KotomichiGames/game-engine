#pragma once

#include "base/context.hpp"

namespace engine::win32
{
    class Context final : public base::Context
    {
    public:
        void create(std::any window_handle) override;
        void destroy()                      override;
        void update()                       override;

    private:
        HDC _dc;
    };
}