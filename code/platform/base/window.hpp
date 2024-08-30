#pragma once

#include "core/window/size.hpp"
#include "core/window/state.hpp"

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
        [[nodiscard]] const   core::size& size()   const
        {
            return _size;
        }
        [[nodiscard]]         core::state state()  const
        {
            return _state;
        }

        Window& title(const std::string& title)
        {
            _title = title;
            return *this;
        }
        Window& state(const core::state  state)
        {
            _state = state;
            return *this;
        }
        Window& size(const  core::size&  size)
        {
            _size = size;
            return *this;
        }

    protected:
        core::state _state { core::state::hidden };
        core::size  _size  { };

        std::string _title;
    };
}