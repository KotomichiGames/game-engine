#include "context.hpp"
#include "macros.hpp"
#include "window.hpp"

namespace engine::win32
{
    void Context::init_wgl_functions()
    {
        Window window;
        window.title("KotomichiGamesDummy").size({ 0, 0 }).create();

        constexpr PIXELFORMATDESCRIPTOR pfd
        {
            .nSize        = sizeof(PIXELFORMATDESCRIPTOR),
            .nVersion     = 1,
            .dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType   = PFD_TYPE_RGBA,
            .cColorBits   = 24
        };
                  const HDC hdc = GetDC(std::any_cast<HWND>(window.handle()));
        if (!SetPixelFormat(hdc,  ChoosePixelFormat(hdc, &pfd), &pfd))
        {
            std::exit(EXIT_FAILURE);
        }

        const HGLRC context = wglCreateContext(hdc);
                              wglMakeCurrent(hdc, context);

        wglCreateContextAttribs = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
        wglChoosePixelFormat    = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));

        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(context);

        window.destroy();
    }

    void Context::create(const std::any window)
    {
        init_wgl_functions();

        constexpr int pixel_attributes[]
        {
            draw_to_window, 1,
            support_opengl, 1,
            double_buffer,  1,
            acceleration,   full_acceleration,
            pixel_type,     type_rgba,
            color_bits,     24,
            depth_bits,     24,
            stencil_bits,   8,
            0
        };

        int32_t  format;
        uint32_t formats;         _hdc = GetDC(std::any_cast<HWND>(window));
        if (!wglChoosePixelFormat(_hdc,  pixel_attributes, nullptr, 1, &format, &formats) || formats == 0)
        {
            std::exit(EXIT_FAILURE);
        }

        PIXELFORMATDESCRIPTOR pfd;
        if (!DescribePixelFormat(_hdc, format, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
        {
            std::exit(EXIT_FAILURE);
        }

        if (!SetPixelFormat(_hdc, format, &pfd))
        {
            std::exit(EXIT_FAILURE);
        }

        constexpr int32_t context_attributes[]
        {
            context_major_version, 4,
            context_minor_version, 6,
            context_profile_mask,  context_core_profile_bit,
            0
        };

        _handle = wglCreateContextAttribs(_hdc, nullptr, context_attributes);
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