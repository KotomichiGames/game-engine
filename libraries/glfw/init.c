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

#include "internal.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

_GLFWlibrary _glfw = { GLFW_FALSE };

static _GLFWerror _glfwMainThreadError;

static void terminate(void)
{
    while (_glfw.windowListHead)
        glfwDestroyWindow((GLFWwindow*) _glfw.windowListHead);

    while (_glfw.cursorListHead)
        glfwDestroyCursor((GLFWcursor*) _glfw.cursorListHead);

    for (int i = 0;  i < _glfw.monitorCount;  i++)
    {
        _GLFWmonitor* monitor = _glfw.monitors[i];
        _glfwFreeMonitor(monitor);
    }

    _glfw_free(_glfw.monitors);
    _glfw.monitors = NULL;
    _glfw.monitorCount = 0;
    _glfw.platform.terminate();

    _glfw.initialized = GLFW_FALSE;

    while (_glfw.errorListHead)
    {
        _GLFWerror* error = _glfw.errorListHead;
        _glfw.errorListHead = error->next;
        _glfw_free(error);
    }

    _glfwPlatformDestroyTls(&_glfw.contextSlot);
    _glfwPlatformDestroyTls(&_glfw.errorSlot);
    _glfwPlatformDestroyMutex(&_glfw.errorLock);

    memset(&_glfw, 0, sizeof(_glfw));
}

char* _glfw_strdup(const char* source)
{
    const size_t length = strlen(source);
    char* result = _glfw_calloc(length + 1, 1);
    strcpy(result, source);
    return result;
}

int _glfw_min(int a, int b)
{
    return a < b ? a : b;
}

void* _glfw_calloc(size_t count, size_t size)
{
    if (count && size)
    {
        if (count > SIZE_MAX / size)
        {
            _glfwInputError(GLFW_INVALID_VALUE, "Allocation size overflow");
            return NULL;
        }

        void* block = malloc(count * size);
        if (block)
            return memset(block, 0, count * size);
        _glfwInputError(GLFW_OUT_OF_MEMORY, NULL);
        return NULL;
    }
    return NULL;
}

void* _glfw_realloc(void* block, size_t size)
{
    if (block && size)
    {
        void* resized = realloc(block, size);
        if (resized)
            return resized;
        _glfwInputError(GLFW_OUT_OF_MEMORY, NULL);
        return NULL;
    }
    if (block)
    {
        free(block);
        return NULL;
    }
    return _glfw_calloc(1, size);
}

void _glfw_free(void* block)
{
    if (block)
        free(block);
}

void _glfwInputError(int code, const char* format, ...)
{
    _GLFWerror* error;
    char description[_GLFW_MESSAGE_SIZE];

    if (format)
    {
        va_list vl;

        va_start(vl, format);
        vsnprintf(description, sizeof(description), format, vl);
        va_end(vl);

        description[sizeof(description) - 1] = '\0';
    }
    else
    {
        if (code == GLFW_NOT_INITIALIZED)
            strcpy(description, "The GLFW library is not initialized");
        else if (code == GLFW_NO_CURRENT_CONTEXT)
            strcpy(description, "There is no current context");
        else if (code == GLFW_INVALID_ENUM)
            strcpy(description, "Invalid argument for enum parameter");
        else if (code == GLFW_INVALID_VALUE)
            strcpy(description, "Invalid value for parameter");
        else if (code == GLFW_OUT_OF_MEMORY)
            strcpy(description, "Out of memory");
        else if (code == GLFW_API_UNAVAILABLE)
            strcpy(description, "The requested API is unavailable");
        else if (code == GLFW_VERSION_UNAVAILABLE)
            strcpy(description, "The requested API version is unavailable");
        else if (code == GLFW_PLATFORM_ERROR)
            strcpy(description, "A platform-specific error occurred");
        else if (code == GLFW_FORMAT_UNAVAILABLE)
            strcpy(description, "The requested format is unavailable");
        else if (code == GLFW_NO_WINDOW_CONTEXT)
            strcpy(description, "The specified window has no context");
        else if (code == GLFW_CURSOR_UNAVAILABLE)
            strcpy(description, "The specified cursor shape is unavailable");
        else if (code == GLFW_FEATURE_UNAVAILABLE)
            strcpy(description, "The requested feature cannot be implemented for this platform");
        else if (code == GLFW_FEATURE_UNIMPLEMENTED)
            strcpy(description, "The requested feature has not yet been implemented for this platform");
        else if (code == GLFW_PLATFORM_UNAVAILABLE)
            strcpy(description, "The requested platform is unavailable");
        else
            strcpy(description, "ERROR: UNKNOWN GLFW ERROR");
    }

    if (_glfw.initialized)
    {
        error = _glfwPlatformGetTls(&_glfw.errorSlot);
        if (!error)
        {
            error = _glfw_calloc(1, sizeof(_GLFWerror));
            _glfwPlatformSetTls(&_glfw.errorSlot, error);
            _glfwPlatformLockMutex(&_glfw.errorLock);
            error->next = _glfw.errorListHead;
            _glfw.errorListHead = error;
            _glfwPlatformUnlockMutex(&_glfw.errorLock);
        }
    }
    else
        error = &_glfwMainThreadError;

    error->code = code;
    strcpy(error->description, description);
}

int glfwInit(void)
{
    if (_glfw.initialized)
        return GLFW_TRUE;

    memset(&_glfw, 0, sizeof(_glfw));

    if (!_glfwSelectPlatform(GLFW_PLATFORM_WIN32, &_glfw.platform))
        return GLFW_FALSE;

    if (!_glfw.platform.init())
    {
        terminate();
        return GLFW_FALSE;
    }

    if (!_glfwPlatformCreateMutex(&_glfw.errorLock) ||
        !_glfwPlatformCreateTls(&_glfw.errorSlot) ||
        !_glfwPlatformCreateTls(&_glfw.contextSlot))
    {
        terminate();
        return GLFW_FALSE;
    }

    _glfwPlatformSetTls(&_glfw.errorSlot, &_glfwMainThreadError);

    _glfwPlatformInitTimer();
    _glfw.timer.offset = _glfwPlatformGetTimerValue();

    _glfw.initialized = GLFW_TRUE;

    glfwDefaultWindowHints();
    return GLFW_TRUE;
}

void glfwTerminate(void)
{
    terminate();
}