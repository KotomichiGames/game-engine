#include "context.hpp"

namespace engine::win32
{
    void Context::create(const std::any handle)
    {
           _hdc = GetDC(std::any_cast<HWND>(handle));

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

        if (const int pixel_format =       ChoosePixelFormat(_hdc, &pixel_descriptor);
                      pixel_format == 0 || SetPixelFormat(_hdc, pixel_format, &pixel_descriptor) == 0)
        {
            std::exit(EXIT_FAILURE);
        }

        _handle = wglCreateContext(_hdc);
                    wglMakeCurrent(_hdc, _handle);
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
}