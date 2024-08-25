#pragma once

#include "buffer.hpp"

#include "base/vertex_attribute.hpp"

namespace engine::gl
{
    class VertexArray final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void attach_vertex_buffer(const Buffer& buffer, int32_t stride) const;

        void attribute(const base::vertex_attribute& attribute) const;
        void bind()    const;
    };
}