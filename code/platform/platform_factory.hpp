#pragma once

#include "base/factory.hpp"

namespace engine
{
    class PlatformFactory
    {
    public:
        static std::shared_ptr<base::Factory> create_factory();
    };
}