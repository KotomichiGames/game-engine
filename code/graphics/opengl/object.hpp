#pragma once

namespace engine::gl
{
    class Object
    {
    public:
        virtual void create()  = 0;
        virtual void destroy() = 0;

        virtual ~Object() = default;

        [[nodiscard, maybe_unused]] uint32_t handle() const
        {
            return _handle;
        }

    protected:
        uint32_t _handle { };
    };
}