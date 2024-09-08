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

        [[maybe_unused]] void push_matrix4(int32_t location, const float* data) const;
    };
}