#pragma once

#include "shader_stage.hpp"

namespace engine::gl
{
    class Shader final : public Object
    {
    public:
        void create()  override;
        void destroy() override;

        void attach(const ShaderStage& stage) const;
        void compile()    const;
        void bind()       const;
    };
}