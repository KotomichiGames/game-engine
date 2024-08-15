#include "factory.hpp"
#include "window.hpp"

namespace engine::glfw
{
    std::unique_ptr<base::Window> Factory::create_window()
    {
        return std::make_unique<Window>();
    }
}