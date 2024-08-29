#pragma once

#include "object.hpp"

#include "core/buffer_data.hpp"

namespace engine::gl
{
    class Buffer final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void data(const core::buffer_data& buffer, uint32_t usage) const;

        void bind(uint32_t location) const;
    };
}
