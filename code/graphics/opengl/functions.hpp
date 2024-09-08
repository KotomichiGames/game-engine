#pragma once

#include "typedefs.hpp"

namespace engine::gl
{
    #pragma region core

    inline PFNGLCLEARPROC        glClear;
    inline PFNGLCLEARCOLORPROC   glClearColor;
    inline PFNGLDRAWARRAYSPROC   glDrawArrays;
    inline PFNGLDRAWELEMENTSPROC glDrawElements;

    #pragma endregion
    #pragma region extended

    inline PFNGLBINDVERTEXARRAYPROC          glBindVertexArray;
    inline PFNGLCREATEVERTEXARRAYSPROC       glCreateVertexArrays;
    inline PFNGLDELETEVERTEXARRAYSPROC       glDeleteVertexArrays;
    inline PFNGLENABLEVERTEXARRAYATTRIBPROC  glEnableVertexArrayAttrib;
    inline PFNGLVERTEXARRAYATTRIBFORMATPROC  glVertexArrayAttribFormat;
    inline PFNGLVERTEXARRAYATTRIBBINDINGPROC glVertexArrayAttribBinding;
    inline PFNGLVERTEXARRAYVERTEXBUFFERPROC  glVertexArrayVertexBuffer;
    inline PFNGLVERTEXARRAYELEMENTBUFFERPROC glVertexArrayElementBuffer;

    inline PFNGLCREATEBUFFERSPROC      glCreateBuffers;
    inline PFNGLDELETEBUFFERSPROC      glDeleteBuffers;
    inline PFNGLNAMEDBUFFERDATAPROC    glNamedBufferData;
    inline PFNGLBINDBUFFERBASEPROC     glBindBufferBase;
    inline PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubData;

    inline PFNGLCREATESHADERPROC     glCreateShader;
    inline PFNGLDELETESHADERPROC     glDeleteShader;
    inline PFNGLSHADERBINARYPROC     glShaderBinary;
    inline PFNGLSPECIALIZESHADERPROC glSpecializeShader;

    inline PFNGLCREATEPROGRAMPROC           glCreateProgram;
    inline PFNGLATTACHSHADERPROC            glAttachShader;
    inline PFNGLLINKPROGRAMPROC             glLinkProgram;
    inline PFNGLUSEPROGRAMPROC              glUseProgram;
    inline PFNGLDELETEPROGRAMPROC           glDeleteProgram;
    inline PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv;

    #pragma endregion

    class Functions
    {
    public:
        static void load_core();
        static void load_extended();

        Functions() = delete;
    };
}