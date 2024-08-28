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
}