/*************************************************************************
 * GLFW 3.5 - www.glfw.org
 * A library for OpenGL, window and input
 *------------------------------------------------------------------------
 * Copyright (c) 2002-2006 Marcus Geelnard
 * Copyright (c) 2006-2018 Camilla Löwy <elmindreda@glfw.org>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would
 *    be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not
 *    be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 *************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(GLFW_NATIVE_INCLUDE_NONE)

 #if defined(GLFW_EXPOSE_NATIVE_WIN32) || defined(GLFW_EXPOSE_NATIVE_WGL)
  /* This is a workaround for the fact that glfw3.h needs to export APIENTRY (for
   * example to allow applications to correctly declare a GL_KHR_debug callback)
   * but windows.h assumes no one will define APIENTRY before it does
   */
  #if defined(GLFW_APIENTRY_DEFINED)
   #undef APIENTRY
   #undef GLFW_APIENTRY_DEFINED
  #endif
  #include <windows.h>
 #endif

#endif /*GLFW_NATIVE_INCLUDE_NONE*/

#if defined(GLFW_EXPOSE_NATIVE_WIN32)
const char* glfwGetWin32Adapter(GLFWmonitor* monitor);
const char* glfwGetWin32Monitor(GLFWmonitor* monitor);
HWND glfwGetWin32Window(GLFWwindow* window);
#endif

#if defined(GLFW_EXPOSE_NATIVE_WGL)
HGLRC glfwGetWGLContext(GLFWwindow* window);
#endif

#ifdef __cplusplus
}
#endif