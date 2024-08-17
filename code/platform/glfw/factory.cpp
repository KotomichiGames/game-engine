#include "factory.hpp"
#include "window.hpp"
#include "platform.hpp"

namespace engine::glfw
{
    std::unique_ptr<base::Window> Factory::create_window()
    {
        return std::make_unique<Window>();
    }

    std::unique_ptr<base::Platform> Factory::create_platform()
    {
        return std::make_unique<Platform>();
    }
}