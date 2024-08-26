#pragma once

#include "object.hpp"

#include "base/buffer_data.hpp"

namespace engine::gl
{
    class Buffer final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void data(const base::buffer_data& buffer, uint32_t usage) const;
    };
}
