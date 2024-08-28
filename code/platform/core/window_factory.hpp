#pragma once

#include "base/factory.hpp"

namespace engine::core
{
    class WindowFactory
    {
    public:
        static std::unique_ptr<base::Factory> create_factory();
    };
}