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

    inline PFNGLCREATEBUFFERSPROC   glCreateBuffers;
    inline PFNGLDELETEBUFFERSPROC   glDeleteBuffers;
    inline PFNGLBINDBUFFERPROC      glBindBuffer;
    inline PFNGLNAMEDBUFFERDATAPROC glNamedBufferData;

    #pragma endregion

    class Functions
    {
    public:
        static void load_core();
        static void load_extended();

        Functions() = delete;
    };
}