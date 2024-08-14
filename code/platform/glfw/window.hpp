#pragma once

namespace engine
{
    class Window
    {
    public:
        void create(const std::string& title, uint32_t width, uint32_t height);
        void update()  const;
        void destroy() const;

        bool is_closed() const;

    private:
        GLFWwindow* _handle { };
    };
}