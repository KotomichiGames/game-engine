#pragma once

#include "typedefs.hpp"

#pragma region core

inline PFNGLCLEARCOLORPROC   glClearColor;
inline PFNGLCLEARPROC        glClear;
inline PFNGLDRAWARRAYSPROC   glDrawArrays;
inline PFNGLDRAWELEMENTSPROC glDrawElements;

#pragma endregion
#pragma region extended

inline PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays;
inline PFNGLBINDVERTEXARRAYPROC    glBindVertexArray;
inline PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

#pragma endregion

namespace engine::gl
{
    class Functions
    {
    public:
        static void load_core();
        static void load_extended();

        Functions() = delete;
    };
}