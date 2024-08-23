#pragma once

#include "base/context.hpp"

#define WGL_CONTEXT_MAJOR_VERSION_ARB    0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB    0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB     0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

using PFNWGLCREATECONTEXTATTRIBSARBPROC = HGLRC(WINAPI*)(HDC, HGLRC, const int32_t*);

inline PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

namespace engine::win32
{
    class Context final : public base::Context
    {
    public:
        void create(std::any handle) override;
        void destroy()               override;
        void update()                override;

    private:
        void init_wgl_functions();

        HGLRC _handle { };
        HDC   _hdc    { };
    };
}