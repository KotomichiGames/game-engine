#pragma once

#ifndef APIENTRY // TODO see if we can remove this at some point
#define APIENTRY
#endif

#pragma region declaration

using PFNGLCLEARCOLORPROC = void(APIENTRY*)(float red, float green, float blue, float alpha);
using PFNGLCLEARPROC      = void(APIENTRY*)(uint32_t mask);

inline PFNGLCLEARCOLORPROC glClearColor;
inline PFNGLCLEARPROC      glClear;

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