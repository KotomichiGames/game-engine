#include "buffer.hpp"
#include "functions.hpp"

namespace engine::gl
{
    void Buffer::create()
    {
        glCreateBuffers(1, &_handle);
    }

    void Buffer::destroy()
    {
        glDeleteBuffers(1, &_handle);
    }

    void Buffer::data(const base::buffer_data& buffer, const uint32_t usage) const
    {
        glNamedBufferData(_handle, buffer.size(), buffer.data(), usage);
    }
}