#pragma once

#include "window_state.hpp"
#include "base/window_size.hpp"

namespace engine::base
{
    class Window
    {
    public:
        virtual void create(const std::string& title) = 0;
        virtual void destroy()                  const = 0;
        virtual void update()                   const = 0;

        virtual ~Window() = default;

        void state(const window_state state)
        {
            _state = state;
        }
        void size(const  window_size& size)
        {
            _size = size;
        }

        [[nodiscard]] const window_size& size()  const
        {
            return _size;
        }
        [[nodiscard]]       window_state state() const
        {
            return _state;
        }

    protected:
        window_state _state { };
        window_size  _size  { };
    };
}