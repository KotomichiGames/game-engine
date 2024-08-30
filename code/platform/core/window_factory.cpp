#include "window_factory.hpp"
#include "win32/factory.hpp"

namespace engine::core
{
    std::unique_ptr<base::Factory> WindowFactory::create_factory()
    {
        return std::make_unique<win32::Factory>();
    }
}