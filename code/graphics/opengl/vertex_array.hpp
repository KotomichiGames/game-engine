#pragma once

#include "object.hpp"

namespace engine::gl
{
    class VertexArray final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void bind()    const;
    };
}