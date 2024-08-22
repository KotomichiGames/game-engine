#pragma once

#pragma region declaration

#ifndef APIENTRY // TODO see if we can remove this at some point
#define APIENTRY
#endif

using PFNGLCLEARCOLORPROC   = void(APIENTRY*)(float red, float green, float blue, float alpha);
using PFNGLCLEARPROC        = void(APIENTRY*)(uint32_t mask);
using PFNGLDRAWARRAYSPROC   = void(APIENTRY*)(uint32_t mode, int32_t first, int32_t count);
using PFNGLDRAWELEMENTSPROC = void(APIENTRY*)(uint32_t mode, int32_t count, uint32_t type, const void* indices);

inline PFNGLCLEARCOLORPROC   glClearColor;
inline PFNGLCLEARPROC        glClear;
inline PFNGLDRAWARRAYSPROC   glDrawArrays;
inline PFNGLDRAWELEMENTSPROC glDrawElements;

#pragma endregion

namespace engine::gl
{
    class Functions
    {
    public:
        static void load();

        Functions() = delete;
    };
}