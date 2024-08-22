#pragma once

#include "base/factory.hpp"

namespace engine
{
    class WindowFactory
    {
    public:
        static std::shared_ptr<base::Factory> create_factory();
    };
}