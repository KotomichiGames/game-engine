#pragma once

#include "base/context.hpp"

#pragma region

using  PFNWGLCREATECONTEXTATTRIBSARBPROC = HGLRC(WINAPI*)(HDC, HGLRC, const int32_t*);
using  PFNWGLCHOOSEPIXELFORMATARBPROC    = BOOL(WINAPI*)(HDC   hdc,   const int32_t*, const float*, uint32_t, int32_t*, uint32_t*);

inline PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
inline PFNWGLCHOOSEPIXELFORMATARBPROC    wglChoosePixelFormatARB;

#pragma endregion

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