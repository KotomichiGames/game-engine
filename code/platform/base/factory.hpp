#pragma once

#include "window.hpp"

namespace engine::base
{
    class Factory
    {
    public:
        virtual std::unique_ptr<Window> create_window() = 0;

        ~Factory() = default;
    };
}