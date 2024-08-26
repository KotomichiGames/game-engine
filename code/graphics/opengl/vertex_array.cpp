#include "vertex_array.hpp"
#include "functions.hpp"

namespace engine::gl
{
    void VertexArray::create()
    {
        glCreateVertexArrays(1, &_handle);
    }

    void VertexArray::destroy()
    {
        glDeleteVertexArrays(1, &_handle);
    }

    void VertexArray::attach_vertex_buffer(const Buffer& buffer, const int32_t stride) const
    {
        glVertexArrayVertexBuffer(_handle, 0, buffer.handle(), 0, stride);
    }

    void VertexArray::attach_indices_buffer(const Buffer& buffer) const
    {
        glVertexArrayElementBuffer(_handle, buffer.handle());
    }

    void VertexArray::attribute(const base::vertex_attribute& attribute) const
    {
        glEnableVertexArrayAttrib(_handle, attribute.index);

        glVertexArrayAttribFormat(_handle,  attribute.index, attribute.size, attribute.type, 0, attribute.offset);
        glVertexArrayAttribBinding(_handle, attribute.index, 0);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(_handle);
    }
}