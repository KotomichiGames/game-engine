#include "shader.hpp"
#include "functions.hpp"

namespace engine::gl
{
    void Shader::create()
    {
        _handle = glCreateProgram();
    }

    void Shader::destroy()
    {
        glDeleteProgram(_handle);
    }

    void Shader::attach(const ShaderStage& stage) const
    {
        glAttachShader(_handle, stage.handle());
    }

    void Shader::compile() const
    {
        glLinkProgram(_handle);
    }

    void Shader::bind() const
    {
        glUseProgram(_handle);
    }

    void Shader::push_matrix4(const int32_t location, const float* data) const
    {
        glProgramUniformMatrix4fv(_handle, location, 1, 0, data);
    }
}