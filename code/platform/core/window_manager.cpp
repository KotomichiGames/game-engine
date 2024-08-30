#include "window_manager.hpp"
#include "window_factory.hpp"

namespace engine::core
{
    void WindowManager::create(const config& config)
    {
        const auto factory = WindowFactory::create_factory();

        _window  = factory->create_window();
        _context = factory->create_context();
        _events  = factory->create_events();

        _window->title(config.title).size(config.size).create();

        _context->create(_window->handle());
    }

    void WindowManager::destroy() const
    {
        _context->destroy();
        _window->destroy();
    }

    void WindowManager::update() const
    {
        _context->update();
        _events->update();
    }

    void WindowManager::open() const
    {
        _window->display();
        _window->state(state::active);
    }

    void WindowManager::close() const
    {
        _window->state(state::closed);
    }

    std::any WindowManager::handle() const
    {
        return _window->handle();
    }

    bool WindowManager::is_active() const
    {
        return _window->state() == state::active;
    }

    int32_t WindowManager::width() const
    {
        return _window->size().width;
    }

    int32_t WindowManager::height() const
    {
        return _window->size().height;
    }
}