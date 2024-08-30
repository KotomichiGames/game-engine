#pragma once

#include "macros.hpp"
#include "object.hpp"

#include "core/buffer_data.hpp"
#include "core/buffer_location.hpp"

namespace engine::gl
{
    class Buffer final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void     data(const core::buffer_data& buffer, uint32_t usage = static_draw) const;
        void sub_data(const core::buffer_data& buffer, int32_t offset = 0)           const;

        void bind(uint32_t location) const;
    };
}
