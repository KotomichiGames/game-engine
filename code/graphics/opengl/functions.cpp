#include "functions.hpp"

namespace engine::gl
{
    void Functions::load_core()
    {
        const HINSTANCE instance = LoadLibrary("opengl32.dll");

        glClear        = reinterpret_cast<PFNGLCLEARPROC>(GetProcAddress(instance, "glClear"));
        glClearColor   = reinterpret_cast<PFNGLCLEARCOLORPROC>(GetProcAddress(instance, "glClearColor"));
        glDrawArrays   = reinterpret_cast<PFNGLDRAWARRAYSPROC>(GetProcAddress(instance, "glDrawArrays"));
        glDrawElements = reinterpret_cast<PFNGLDRAWELEMENTSPROC>(GetProcAddress(instance, "glDrawElements"));

        FreeLibrary(instance);
    }

    void Functions::load_extended()
    {
        glCreateVertexArrays = reinterpret_cast<PFNGLCREATEVERTEXARRAYSPROC>(wglGetProcAddress("glCreateVertexArrays"));
        glBindVertexArray    = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));
        glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(wglGetProcAddress("glDeleteVertexArrays"));

        glCreateBuffers   = reinterpret_cast<PFNGLCREATEBUFFERSPROC>(wglGetProcAddress("glCreateBuffers"));
        glDeleteBuffers   = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(wglGetProcAddress("glDeleteBuffers"));
        glBindBuffer      = reinterpret_cast<PFNGLBINDBUFFERPROC>(wglGetProcAddress("glBindBuffer"));
        glNamedBufferData = reinterpret_cast<PFNGLNAMEDBUFFERDATAPROC>(wglGetProcAddress("glNamedBufferData"));
    }
}