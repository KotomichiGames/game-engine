#pragma once

namespace engine::core
{
    class buffer_data
    {
    public:
        template <typename T> static buffer_data create_from(const std::vector<T>& buffer)
        {
            return { buffer.data(), static_cast<uint32_t>(buffer.size() * sizeof(T)) };
        }
        template <typename T> static buffer_data create_from(const T* data)
        {
            return { data, static_cast<uint32_t>(sizeof(T)) };
        }

        [[nodiscard]] const void* data() const
        {
            assert(_data);
            return _data;
        }
        [[nodiscard]] uint32_t    size() const
        {
            return _size;
        }

    private:
        buffer_data(const void* data, const uint32_t size)
            : _data { data }
            , _size { size }
        {
        }

        const void* _data { };
        uint32_t    _size { };
    };
}