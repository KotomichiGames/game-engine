#pragma once

namespace engine::base
{
    class Context
    {
    public:
        virtual void create(std::any window_handle) = 0;
        virtual void destroy()                      = 0;

        virtual ~Context() = default;
    };
}