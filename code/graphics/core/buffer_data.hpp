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

        [[nodiscard]] const void* data() const;
        [[nodiscard]] uint32_t    size() const;

    private:
        buffer_data(const void* data, uint32_t size);

        const void* _data { };
        uint32_t    _size { };
    };
}