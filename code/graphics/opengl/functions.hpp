#pragma once

#ifndef APIENTRY
#define APIENTRY
#endif

using GLfloat    = float;
using GLbitfield = uint32_t;

using PFNGLCLEARCOLORPROC = void(APIENTRY*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
using PFNGLCLEARPROC      = void(APIENTRY*)(GLbitfield mask);

namespace engine::gl
{
    inline PFNGLCLEARCOLORPROC glClearColor;
    inline PFNGLCLEARPROC      glClear;

    class Functions
    {
    public:
        static void load();

        Functions() = delete;
    };
}