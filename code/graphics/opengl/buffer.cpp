#include "buffer.hpp"
#include "functions.hpp"
#include "macros.hpp"

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

    void Buffer::data(const core::buffer_data& buffer, const uint32_t usage) const
    {
        glNamedBufferData(_handle, buffer.size(), buffer.data(), usage);
    }

    void Buffer::sub_data(const core::buffer_data& buffer, const int32_t offset) const
    {
        glNamedBufferSubData(_handle, offset, buffer.size(), buffer.data());
    }

    void Buffer::bind(const uint32_t location) const
    {
        glBindBufferBase(uniform_buffer, location, _handle);
    }
}