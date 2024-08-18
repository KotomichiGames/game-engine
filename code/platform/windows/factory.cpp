#include "factory.hpp"
#include "window.hpp"
#include "platform.hpp"
#include "context.hpp"

namespace engine::win32
{
    std::unique_ptr<base::Window> Factory::create_window()
    {
        return std::make_unique<Window>();
    }

    std::unique_ptr<base::Platform> Factory::create_platform()
    {
        return std::make_unique<Platform>();
    }

    std::unique_ptr<base::Context> Factory::create_context()
    {
        return std::make_unique<Context>();
    }
}