#pragma once

namespace engine::core
{
    struct attribute
    {
        uint32_t index;
         int32_t  size;
        uint32_t  type;
        uint32_t offset { };
    };
}