#pragma once

namespace engine::gl
{
    class Commands
    {
    public:
        static void clear(float red, float green, float blue, float alpha = 1.0f);
        static void clear(uint32_t flags);

        Commands() = delete;
    };
}