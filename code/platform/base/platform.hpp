#pragma once

namespace engine::base
{
    class Platform
    {
    public:
        virtual void update()  const = 0;

        virtual  ~Platform() = default;
    };
}