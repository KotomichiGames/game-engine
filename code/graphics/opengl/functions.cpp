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
        glBindVertexArray          = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));
        glCreateVertexArrays       = reinterpret_cast<PFNGLCREATEVERTEXARRAYSPROC>(wglGetProcAddress("glCreateVertexArrays"));
        glDeleteVertexArrays       = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(wglGetProcAddress("glDeleteVertexArrays"));
        glEnableVertexArrayAttrib  = reinterpret_cast<PFNGLENABLEVERTEXARRAYATTRIBPROC>(wglGetProcAddress("glEnableVertexArrayAttrib"));
        glVertexArrayAttribFormat  = reinterpret_cast<PFNGLVERTEXARRAYATTRIBFORMATPROC>(wglGetProcAddress("glVertexArrayAttribFormat"));
        glVertexArrayAttribBinding = reinterpret_cast<PFNGLVERTEXARRAYATTRIBBINDINGPROC>(wglGetProcAddress("glVertexArrayAttribBinding"));
        glVertexArrayVertexBuffer  = reinterpret_cast<PFNGLVERTEXARRAYVERTEXBUFFERPROC>(wglGetProcAddress("glVertexArrayVertexBuffer"));
        glVertexArrayElementBuffer = reinterpret_cast<PFNGLVERTEXARRAYELEMENTBUFFERPROC>(wglGetProcAddress("glVertexArrayElementBuffer"));

        glCreateBuffers   = reinterpret_cast<PFNGLCREATEBUFFERSPROC>(wglGetProcAddress("glCreateBuffers"));
        glDeleteBuffers   = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(wglGetProcAddress("glDeleteBuffers"));
        glNamedBufferData = reinterpret_cast<PFNGLNAMEDBUFFERDATAPROC>(wglGetProcAddress("glNamedBufferData"));

        glCreateShader     = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));
        glDeleteShader     = reinterpret_cast<PFNGLDELETESHADERPROC>(wglGetProcAddress("glDeleteShader"));
        glShaderBinary     = reinterpret_cast<PFNGLSHADERBINARYPROC>(wglGetProcAddress("glShaderBinary"));
        glSpecializeShader = reinterpret_cast<PFNGLSPECIALIZESHADERPROC>(wglGetProcAddress("glSpecializeShader"));
    }
}