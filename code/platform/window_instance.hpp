#pragma once

#include "base/factory.hpp"

namespace engine
{
    class WindowInstance
    {
    public:
        void create(const std::shared_ptr<base::Factory>& factory, const std::string& title);
        void destroy();
        void update();
        void close();

        [[nodiscard]] bool is_active() const;

        static WindowInstance& instance();

    private:
        std::unique_ptr<base::Window> _window;
    };
}