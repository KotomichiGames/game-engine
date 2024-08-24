#include "window_factory.hpp"
#include "win32/factory.hpp"

namespace engine
{
    std::shared_ptr<base::Factory> WindowFactory::create_factory()
    {
        return std::make_shared<win32::Factory>();
    }
}