#include "window_instance.hpp"

namespace engine
{
    void WindowInstance::create(const std::shared_ptr<base::Factory>& factory, const base::window_config& config)
    {
        _window = factory->create_window();

        _window->size(config.size);
        _window->create(config.title);
    }

    void WindowInstance::destroy()
    {
        _window->destroy();
    }

    void WindowInstance::update()
    {
        _window->update();
    }

    void WindowInstance::close()
    {
        _window->state(base::window_state::closed);
    }

    bool WindowInstance::is_active() const
    {
        return _window->state() == base::window_state::active;
    }

    WindowInstance& WindowInstance::instance()
    {
        static WindowInstance instance;
        return instance;
    }
}