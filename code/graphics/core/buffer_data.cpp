#include "buffer_data.hpp"

namespace engine::core
{
    buffer_data::buffer_data(const void* data, const uint32_t size)
        : _data { data }
        , _size { size }
    {
    }

    const void* buffer_data::data() const
    {
        assert(_data);
        return _data;
    }

    uint32_t buffer_data::size() const
    {
        return _size;
    }
}