#pragma once

#include "base/factory.hpp"
#include "base/window_config.hpp"

namespace engine
{
    class WindowInstance
    {
    public:
        void create(const std::shared_ptr<base::Factory>& factory, const base::window_config& config);
        void destroy();
        void update();
        void close();

        [[nodiscard]] bool is_active() const;

        static WindowInstance& instance();

    private:
        std::unique_ptr<base::Window> _window;
    };
}