#include "context.hpp"

namespace engine::win32
{
    void Context::create(const std::any handle)
    {
        init_wgl_functions();

        constexpr PIXELFORMATDESCRIPTOR pixel_descriptor
        {
            .nSize        = sizeof(PIXELFORMATDESCRIPTOR),
            .nVersion     = 1,
            .dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType   = PFD_TYPE_RGBA,
            .cColorBits   = 24,
            .cDepthBits   = 24,
            .cStencilBits = 8,
            .iLayerType   = PFD_MAIN_PLANE
        };

        _hdc = GetDC(std::any_cast<HWND>(handle));

        if (const int pixel_format =       ChoosePixelFormat(_hdc, &pixel_descriptor);
                      pixel_format == 0 || SetPixelFormat(_hdc, pixel_format, &pixel_descriptor) == 0) {
            std::exit(EXIT_FAILURE);
        }

        _handle = wglCreateContext(_hdc);
                    wglMakeCurrent(_hdc, _handle);

        /*
        wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));


        constexpr int32_t attributes[]
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 6,
            WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        _handle = wglCreateContextAttribsARB(_hdc, nullptr, attributes);
        wglMakeCurrent(_hdc, _handle);
        */
    }

    void Context::destroy()
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(_handle);
    }

    void Context::update()
    {
        SwapBuffers(_hdc);
    }

    void Context::init_wgl_functions()
    {
    }
}