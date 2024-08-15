#pragma once

namespace engine::base
{
    class Window
    {
    public:
        virtual void create(const std::string& title, int32_t width, int32_t height) = 0;
        virtual void update()  const = 0;
        virtual void destroy() const = 0;

        virtual [[nodiscard]] bool is_closed() const = 0;
    };
}