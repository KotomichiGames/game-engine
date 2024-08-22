#include "window_factory.hpp"

#ifdef WIN32
#include "glfw/factory.hpp"
#endif

namespace engine
{
    std::shared_ptr<base::Factory> WindowFactory::create_factory()
    {
        #ifdef WIN32
        return std::make_shared<glfw::Factory>();
        #endif
    }
}