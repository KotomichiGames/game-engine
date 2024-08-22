#include "functions.hpp"

namespace engine::gl
{
    void Functions::load()
    {
        glClearColor = reinterpret_cast<PFNGLCLEARCOLORPROC>(wglGetProcAddress("glClearColor"));
        glClear      = reinterpret_cast<PFNGLCLEARPROC>(wglGetProcAddress("glClear"));
    }
}