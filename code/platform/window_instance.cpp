#include "window_instance.hpp"

namespace engine
{
    void WindowInstance::create(const std::shared_ptr<base::Factory>& factory, const base::window_config& config)
    {
        _window = factory->create_window();

        _window->size(config.size);
        _window->create(config.title);
    }

    void WindowInstance::destroy() const
    {
        _window->destroy();
    }

    void WindowInstance::open() const
    {
        _window->display();
    }

    void WindowInstance::close() const
    {
        _window->state(base::window_state::closed);
    }

    std::any WindowInstance::handle() const
    {
        return _window->handle();
    }

    bool WindowInstance::is_active() const
    {
        return _window->state() == base::window_state::active;
    }

    int32_t WindowInstance::width() const
    {
        return _window->size().width;
    }

    int32_t WindowInstance::height() const
    {
        return _window->size().height;
    }

    WindowInstance& WindowInstance::instance()
    {
        static WindowInstance instance;
        return instance;
    }
}