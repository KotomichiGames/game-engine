#pragma once

namespace engine::data
{
    template <typename V> struct geometry
    {
        std::vector<V>        vertices;
        std::vector<uint32_t> indices;
    };
}