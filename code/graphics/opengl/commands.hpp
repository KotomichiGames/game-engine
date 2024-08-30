#pragma once

#include "core/rgb.hpp"

namespace engine::gl
{
    class Commands
    {
    public:
        static void clear(const core::rgb& color, float alpha = 1.0f);
        static void clear(uint32_t flags);

        static void draw_arrays(uint32_t   primitive, int32_t count);
        static void draw_elements(uint32_t primitive, int32_t count);

        Commands() = delete;
    };
}