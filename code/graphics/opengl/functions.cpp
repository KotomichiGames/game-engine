#include "functions.hpp"

namespace engine::gl
{
    void Functions::load()
    {
        const HINSTANCE instance = LoadLibrary("opengl32.dll");

        glClearColor   = reinterpret_cast<PFNGLCLEARCOLORPROC>(GetProcAddress(instance, "glClearColor"));
        glClear        = reinterpret_cast<PFNGLCLEARPROC>(GetProcAddress(instance, "glClear"));
        glDrawArrays   = reinterpret_cast<PFNGLDRAWARRAYSPROC>(GetProcAddress(instance, "glDrawArrays"));
        glDrawElements = reinterpret_cast<PFNGLDRAWELEMENTSPROC>(GetProcAddress(instance, "glDrawElements"));

        FreeLibrary(instance);
    }
}