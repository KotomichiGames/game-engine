#pragma once

namespace engine::base
{
    class Context
    {
    public:
        virtual void create(std::any window) = 0;
        virtual void destroy()               = 0;
        virtual void update()                = 0;

        virtual ~Context() = default;
    };
}