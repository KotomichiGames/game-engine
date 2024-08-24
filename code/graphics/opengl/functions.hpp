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

    inline PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays;
    inline PFNGLBINDVERTEXARRAYPROC    glBindVertexArray;
    inline PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

    #pragma endregion

    class Functions
    {
    public:
        static void load_core();
        static void load_extended();

        Functions() = delete;
    };
}