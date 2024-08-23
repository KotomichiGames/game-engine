#include "window_manager.hpp"

namespace engine
{
    void WindowManager::create(const std::shared_ptr<base::Factory>& factory, const base::window_config& config)
    {
        _window  = factory->create_window();
        _context = factory->create_context();
        _events  = factory->create_events();

        _window->size(config.size);
        _window->title(config.title);
        _window->create();

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
    }

    void WindowManager::close() const
    {
        _window->state(base::window_state::closed);
    }

    std::any WindowManager::handle() const
    {
        return _window->handle();
    }

    bool WindowManager::is_active() const
    {
        return _window->state() == base::window_state::active;
    }

    int32_t WindowManager::width() const
    {
        return _window->size().width;
    }

    int32_t WindowManager::height() const
    {
        return _window->size().height;
    }

    WindowManager& WindowManager::instance()
    {
        static WindowManager instance;
        return instance;
    }
}