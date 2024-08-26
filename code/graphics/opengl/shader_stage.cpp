#include "shader_stage.hpp"
#include "functions.hpp"

namespace engine::gl
{
    ShaderStage::ShaderStage(const uint32_t type)
        : _type { type }
    {
    }

    void ShaderStage::create()
    {
        _handle = glCreateShader(_type);
    }

    void ShaderStage::destroy()
    {
        glDeleteShader(_handle);
    }
}