#pragma once

#include "window_state.hpp"

namespace engine::base
{
    class Window
    {
    public:
        virtual void create(const std::string& title, int32_t width, int32_t height) = 0;
        virtual void update()  const = 0;
        virtual void destroy() const = 0;

        virtual ~Window() = default;

        void state(const window_state state)
        {
            _state = state;
        }

        [[nodiscard]] window_state state() const
        {
            return _state;
        }

    private:
        window_state _state;
    };
}