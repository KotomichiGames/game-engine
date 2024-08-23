#include "context.hpp"
#include "macros.hpp"

namespace engine::win32
{
    void Context::init_wgl_functions()
    {
        const WNDCLASSEX   wndclassex // TODO maybe use our window here?
        {
            .cbSize        = sizeof(WNDCLASSEX),
            .style         = CS_OWNDC,
            .lpfnWndProc   = DefWindowProc,
            .hInstance     = GetModuleHandle(nullptr),
            .lpszClassName = "KotomichiGamesDummy",
        };

        const ATOM wc   = RegisterClassEx(&wndclassex);
        const HWND hwnd = CreateWindowEx(0, MAKEINTATOM(wc), "KotomichiGamesDummy" , 0, 0, 0, 0, 0, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
        const HDC  hdc  = GetDC(hwnd);

        constexpr PIXELFORMATDESCRIPTOR pfd
        {
            .nSize        = sizeof(PIXELFORMATDESCRIPTOR),
            .nVersion     = 1,
            .dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType   = PFD_TYPE_RGBA,
            .cColorBits   = 24
        };

        if (!SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd))
        {
            std::exit(EXIT_FAILURE);
        }

        const HGLRC context = wglCreateContext(hdc);
                              wglMakeCurrent(hdc, context);

        wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
        wglChoosePixelFormatARB    = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));

        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(context);

        ReleaseDC(hwnd, hdc);
        DestroyWindow(hwnd);

        UnregisterClass(MAKEINTATOM(wc), GetModuleHandle(nullptr));
    }

    void Context::create(const std::any handle)
    {
        init_wgl_functions();

        constexpr int pixel_attributes[]
        {
            draw_to_window_arb, 1,
            support_opengl_arb, 1,
            double_buffer_arb,  1,
            pixel_type_arb,     type_rgba_arb,
            color_bits_arb,     32,
            depth_bits_arb,     24,
            stencil_bits_arb,   8,
            0
        };

        int32_t  format;
        uint32_t formats;
                                     _hdc = GetDC(std::any_cast<HWND>(handle));
        if (!wglChoosePixelFormatARB(_hdc,  pixel_attributes, nullptr, 1, &format, &formats) || formats == 0)
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
            context_major_version_arb, 4,
            context_minor_version_arb, 6,
            context_profile_mask_arb,  context_core_profile_bit_arb,
            0
        };

        _handle = wglCreateContextAttribsARB(_hdc, nullptr, context_attributes);
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