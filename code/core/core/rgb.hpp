#pragma once

namespace engine::core
{
    struct rgb
    {
        float r;
        float g;
        float b;
    };

    namespace color
    {
        static constexpr rgb white { 1.0f, 1.0f, 1.0f };
        static constexpr rgb black { 0.0f, 0.0f, 0.0f };
        static constexpr rgb gray  { 0.5f, 0.5f, 0.5f };
    }
}