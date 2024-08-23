#include "factory.hpp"
#include "window.hpp"
#include "context.hpp"
#include "window_events.hpp"

namespace engine::win32
{
    std::unique_ptr<base::Window> Factory::create_window()
    {
        return std::make_unique<Window>();
    }

    std::unique_ptr<base::WindowEvents> Factory::create_events()
    {
        return std::make_unique<WindowEvents>();
    }

    std::unique_ptr<base::Context> Factory::create_context()
    {
        return std::make_unique<Context>();
    }
}