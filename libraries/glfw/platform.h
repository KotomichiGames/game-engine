//========================================================================
// GLFW 3.5 - www.glfw.org
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2018 Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#pragma once

#if defined(_GLFW_WIN32)
 #include "win32_platform.h"
#define GLFW_EXPOSE_NATIVE_WIN32
 #define GLFW_EXPOSE_NATIVE_WGL
#endif

#define GLFW_PLATFORM_WINDOW_STATE \
        GLFW_WIN32_WINDOW_STATE \

#define GLFW_PLATFORM_MONITOR_STATE \
        GLFW_WIN32_MONITOR_STATE \

#define GLFW_PLATFORM_CURSOR_STATE \
        GLFW_WIN32_CURSOR_STATE \

#define GLFW_PLATFORM_LIBRARY_WINDOW_STATE \
        GLFW_WIN32_LIBRARY_WINDOW_STATE \

#define GLFW_PLATFORM_CONTEXT_STATE \
        GLFW_WGL_CONTEXT_STATE \

#define GLFW_PLATFORM_LIBRARY_CONTEXT_STATE \
        GLFW_WGL_LIBRARY_CONTEXT_STATE \

#if defined(_WIN32)
 #define GLFW_BUILD_WIN32_THREAD
#endif

#if defined(GLFW_BUILD_WIN32_THREAD)
 #include "win32_thread.h"
 #define GLFW_PLATFORM_TLS_STATE    GLFW_WIN32_TLS_STATE
 #define GLFW_PLATFORM_MUTEX_STATE  GLFW_WIN32_MUTEX_STATE
#endif

#if defined(_WIN32)
 #define GLFW_BUILD_WIN32_TIMER
#endif

#if defined(GLFW_BUILD_WIN32_TIMER)
 #include "win32_time.h"
 #define GLFW_PLATFORM_LIBRARY_TIMER_STATE  GLFW_WIN32_LIBRARY_TIMER_STATE
#endif