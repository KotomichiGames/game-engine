#pragma once

#include "object.hpp"

namespace engine::gl
{
    class ShaderStage final : public Object
    {
    public:
        explicit ShaderStage(uint32_t type);

        void create()  override;
        void destroy() override;

    private:
        uint32_t _type;
    };
}