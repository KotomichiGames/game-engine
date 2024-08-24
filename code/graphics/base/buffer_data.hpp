#pragma once

namespace engine::base
{
    class buffer_data
    {
    public:
        template <typename buffer_t>  static buffer_data create_from(const std::vector<buffer_t>& buffer)
        {
            return { buffer.data(), static_cast<uint32_t>(buffer.size() * sizeof(buffer_t)) };
        }

        [[nodiscard]] const void* data() const
        {
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