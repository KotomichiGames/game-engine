#pragma once

#pragma region

using  PFNWGLCREATECONTEXTATTRIBSARBPROC = HGLRC(WINAPI*)(HDC, HGLRC, const int32_t*);
using  PFNWGLCHOOSEPIXELFORMATARBPROC    = BOOL(WINAPI*)(HDC   hdc,   const int32_t*, const float*, uint32_t, int32_t*, uint32_t*);

#pragma endregion

#include "base/context.hpp"

namespace engine::win32
{
    inline PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribs;
    inline PFNWGLCHOOSEPIXELFORMATARBPROC    wglChoosePixelFormat;

    class Context final : public base::Context
    {
    public:
        void create(std::any window) override;
        void destroy()               override;
        void update()                override;

    private:
        static void init_wgl_functions();

        HGLRC _handle { };
        HDC   _hdc    { };
    };
}