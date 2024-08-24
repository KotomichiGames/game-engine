#pragma once

#include "base/factory.hpp"
#include "base/window_config.hpp"

namespace engine::core
{
    class WindowManager
    {
    public:
        void create(const std::shared_ptr<base::Factory>& factory, const base::window_config& config);
        void destroy()    const;
        void update()     const;

        void open()       const;
        void close()      const;

        [[nodiscard]] std::any handle() const;
        [[nodiscard]] bool  is_active() const;

        [[nodiscard]] int32_t   width() const;
        [[nodiscard]] int32_t  height() const;

        WindowManager& operator=(const WindowManager&) = delete;
        WindowManager(const WindowManager&)            = delete;

        static WindowManager& instance();

    private:
        std::unique_ptr<base::Window>       _window;
        std::unique_ptr<base::WindowEvents> _events;
        std::unique_ptr<base::Context>     _context;

        WindowManager() = default;
    };
}