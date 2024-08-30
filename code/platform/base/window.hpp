#pragma once

#include "base/window_size.hpp"
#include "base/window_state.hpp"

namespace engine::base
{
    class Window
    {
    public:
        virtual void create()        = 0;
        virtual void destroy() const = 0;
        virtual void display() const = 0;

        virtual ~Window() =  default;

        [[nodiscard]] virtual std::any    handle() const = 0;
        [[nodiscard]] const   std::string& title() const
        {
            return _title;
        }
        [[nodiscard]] const   window_size& size()  const
        {
            return _size;
        }
        [[nodiscard]]         window_state state() const
        {
            return _state;
        }

        Window& title(const std::string& title)
        {
            _title = title;
            return *this;
        }
        Window& state(const window_state state)
        {
            _state = state;
            return *this;
        }
        Window& size(const  window_size& size)
        {
            _size = size;
            return *this;
        }

    protected:
        window_state _state { window_state::hidden };
        window_size  _size  { };

        std::string  _title;
    };
}