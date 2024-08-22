#include "functions.hpp"

namespace engine::gl
{
    void Functions::load()
    {
        const HINSTANCE instance = LoadLibrary("opengl32.dll");

        glClearColor = reinterpret_cast<PFNGLCLEARCOLORPROC>(GetProcAddress(instance, "glClearColor"));
        glClear      = reinterpret_cast<PFNGLCLEARPROC>(GetProcAddress(instance, "glClear"));

        FreeLibrary(instance);
    }
}