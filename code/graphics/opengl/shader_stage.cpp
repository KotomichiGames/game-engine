#include "shader_stage.hpp"
#include "functions.hpp"
#include "macros.hpp"

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

    void ShaderStage::source(const std::vector<char>& source) const
    {
        glShaderBinary(1, &_handle, shader_binary_format, source.data(), source.size());
        glSpecializeShader(_handle, "main", 0, nullptr, nullptr);
    }
}