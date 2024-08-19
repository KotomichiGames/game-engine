//========================================================================
// GLFW 3.5 - www.glfw.org
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2019 Camilla Löwy <elmindreda@glfw.org>
// Copyright (c) 2012 Torsten Walluhn <tw@mad-cad.net>
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

#include <assert.h>
#include <string.h>
#include <stdlib.h>

void _glfwInputWindowFocus(_GLFWwindow* window, GLFWbool focused)
{
    assert(window != NULL);
    assert(focused == GLFW_TRUE || focused == GLFW_FALSE);

    if (window->callbacks.focus)
        window->callbacks.focus((GLFWwindow*) window, focused);

    if (!focused)
    {
        for (int key = 0;  key <= GLFW_KEY_LAST;  key++)
        {
            if (window->keys[key] == GLFW_PRESS)
            {
                _glfwInputKey(window, key, GLFW_RELEASE, 0);
            }
        }

        for (int button = 0;  button <= GLFW_MOUSE_BUTTON_LAST;  button++)
        {
            if (window->mouseButtons[button] == GLFW_PRESS)
                _glfwInputMouseClick(window, button, GLFW_RELEASE, 0);
        }
    }
}

void _glfwInputWindowSize(_GLFWwindow* window, int width, int height)
{
    assert(window != NULL);
    assert(width >= 0);
    assert(height >= 0);

    if (window->callbacks.size)
        window->callbacks.size((GLFWwindow*) window, width, height);
}

void _glfwInputWindowIconify(_GLFWwindow* window, GLFWbool iconified)
{
    assert(window != NULL);
    assert(iconified == GLFW_TRUE || iconified == GLFW_FALSE);

    if (window->callbacks.iconify)
        window->callbacks.iconify((GLFWwindow*) window, iconified);
}

void _glfwInputWindowMaximize(_GLFWwindow* window, GLFWbool maximized)
{
    assert(window != NULL);
    assert(maximized == GLFW_TRUE || maximized == GLFW_FALSE);

    if (window->callbacks.maximize)
        window->callbacks.maximize((GLFWwindow*) window, maximized);
}

void _glfwInputFramebufferSize(_GLFWwindow* window, int width, int height)
{
    assert(window != NULL);
    assert(width >= 0);
    assert(height >= 0);

    if (window->callbacks.fbsize)
        window->callbacks.fbsize((GLFWwindow*) window, width, height);
}

void _glfwInputWindowDamage(_GLFWwindow* window)
{
    assert(window != NULL);

    if (window->callbacks.refresh)
        window->callbacks.refresh((GLFWwindow*) window);
}

void _glfwInputWindowCloseRequest(_GLFWwindow* window)
{
    if (window->callbacks.close)
        window->callbacks.close();
}

void _glfwInputWindowMonitor(_GLFWwindow* window, _GLFWmonitor* monitor)
{
    assert(window != NULL);
    window->monitor = monitor;
}

GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor)
{
    _GLFWfbconfig fbconfig;
    _GLFWctxconfig ctxconfig;
    _GLFWwndconfig wndconfig;

    assert(title != NULL);
    assert(width >= 0);
    assert(height >= 0);

    if (width <= 0 || height <= 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid window size %ix%i", width, height);
        return NULL;
    }

    fbconfig  = _glfw.hints.framebuffer;
    ctxconfig = _glfw.hints.context;
    wndconfig = _glfw.hints.window;

    wndconfig.width   = width;
    wndconfig.height  = height;
    wndconfig.title   = title;

    if (!_glfwIsValidContextConfig(&ctxconfig))
        return NULL;

    _GLFWwindow* window = _glfw_calloc(1, sizeof(_GLFWwindow));
    window->next = _glfw.windowListHead;
    _glfw.windowListHead = window;

    window->videoMode.width       = width;
    window->videoMode.height      = height;
    window->videoMode.redBits     = fbconfig.redBits;
    window->videoMode.greenBits   = fbconfig.greenBits;
    window->videoMode.blueBits    = fbconfig.blueBits;
    window->videoMode.refreshRate = _glfw.hints.refreshRate;

    window->monitor          = (_GLFWmonitor*) monitor;
    window->resizable        = wndconfig.resizable;
    window->decorated        = wndconfig.decorated;
    window->autoIconify      = wndconfig.autoIconify;
    window->floating         = wndconfig.floating;
    window->mousePassthrough = wndconfig.mousePassthrough;
    window->cursorMode       = GLFW_CURSOR_NORMAL;

    window->doublebuffer = fbconfig.doublebuffer;

    window->minwidth    = GLFW_DONT_CARE;
    window->minheight   = GLFW_DONT_CARE;
    window->maxwidth    = GLFW_DONT_CARE;
    window->maxheight   = GLFW_DONT_CARE;
    window->numer       = GLFW_DONT_CARE;
    window->denom       = GLFW_DONT_CARE;
    window->title       = _glfw_strdup(title);

    if (!_glfw.platform.createWindow(window, &wndconfig, &ctxconfig, &fbconfig))
    {
        glfwDestroyWindow((GLFWwindow*) window);
        return NULL;
    }

    return (GLFWwindow*) window;
}

void glfwDefaultWindowHints(void)
{
    // The default is OpenGL with minimum version 1.0
    memset(&_glfw.hints.context, 0, sizeof(_glfw.hints.context));
    _glfw.hints.context.client = GLFW_OPENGL_API;
    _glfw.hints.context.source = GLFW_NATIVE_CONTEXT_API;
    _glfw.hints.context.major  = 4;
    _glfw.hints.context.minor  = 6;

    // The default is a focused, visible, resizable window with decorations
    memset(&_glfw.hints.window, 0, sizeof(_glfw.hints.window));
    _glfw.hints.window.resizable    = GLFW_TRUE;
    _glfw.hints.window.visible      = GLFW_TRUE;
    _glfw.hints.window.decorated    = GLFW_TRUE;
    _glfw.hints.window.focused      = GLFW_TRUE;
    _glfw.hints.window.autoIconify  = GLFW_TRUE;
    _glfw.hints.window.centerCursor = GLFW_TRUE;
    _glfw.hints.window.xpos         = GLFW_ANY_POSITION;
    _glfw.hints.window.ypos         = GLFW_ANY_POSITION;
    _glfw.hints.window.scaleFramebuffer = GLFW_TRUE;

    // The default is 24 bits of color, 24 bits of depth and 8 bits of stencil,
    // double buffered
    memset(&_glfw.hints.framebuffer, 0, sizeof(_glfw.hints.framebuffer));
    _glfw.hints.framebuffer.redBits      = 8;
    _glfw.hints.framebuffer.greenBits    = 8;
    _glfw.hints.framebuffer.blueBits     = 8;
    _glfw.hints.framebuffer.alphaBits    = 8;
    _glfw.hints.framebuffer.depthBits    = 24;
    _glfw.hints.framebuffer.stencilBits  = 8;
    _glfw.hints.framebuffer.doublebuffer = GLFW_TRUE;

    // The default is to select the highest available refresh rate
    _glfw.hints.refreshRate = GLFW_DONT_CARE;
}

void glfwWindowHint(int hint, int value)
{
    switch (hint)
    {
        case GLFW_RED_BITS:
            _glfw.hints.framebuffer.redBits = value;
            return;
        case GLFW_GREEN_BITS:
            _glfw.hints.framebuffer.greenBits = value;
            return;
        case GLFW_BLUE_BITS:
            _glfw.hints.framebuffer.blueBits = value;
            return;
        case GLFW_ALPHA_BITS:
            _glfw.hints.framebuffer.alphaBits = value;
            return;
        case GLFW_DEPTH_BITS:
            _glfw.hints.framebuffer.depthBits = value;
            return;
        case GLFW_STENCIL_BITS:
            _glfw.hints.framebuffer.stencilBits = value;
            return;
        case GLFW_AUX_BUFFERS:
            _glfw.hints.framebuffer.auxBuffers = value;
            return;
        case GLFW_STEREO:
            _glfw.hints.framebuffer.stereo = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_DOUBLEBUFFER:
            _glfw.hints.framebuffer.doublebuffer = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_SAMPLES:
            _glfw.hints.framebuffer.samples = value;
            return;
        case GLFW_SRGB_CAPABLE:
            _glfw.hints.framebuffer.sRGB = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_RESIZABLE:
            _glfw.hints.window.resizable = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_DECORATED:
            _glfw.hints.window.decorated = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_FOCUSED:
            _glfw.hints.window.focused = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_AUTO_ICONIFY:
            _glfw.hints.window.autoIconify = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_FLOATING:
            _glfw.hints.window.floating = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_MAXIMIZED:
            _glfw.hints.window.maximized = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_VISIBLE:
            _glfw.hints.window.visible = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_POSITION_X:
            _glfw.hints.window.xpos = value;
            return;
        case GLFW_POSITION_Y:
            _glfw.hints.window.ypos = value;
            return;
        case GLFW_SCALE_TO_MONITOR:
            _glfw.hints.window.scaleToMonitor = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_SCALE_FRAMEBUFFER:
            _glfw.hints.window.scaleFramebuffer = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CENTER_CURSOR:
            _glfw.hints.window.centerCursor = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_MOUSE_PASSTHROUGH:
            _glfw.hints.window.mousePassthrough = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CLIENT_API:
            _glfw.hints.context.client = value;
            return;
        case GLFW_CONTEXT_CREATION_API:
            _glfw.hints.context.source = value;
            return;
        case GLFW_CONTEXT_ROBUSTNESS:
            _glfw.hints.context.robustness = value;
            return;
        case GLFW_CONTEXT_NO_ERROR:
            _glfw.hints.context.noerror = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_OPENGL_PROFILE:
            _glfw.hints.context.profile = value;
            return;
        case GLFW_CONTEXT_RELEASE_BEHAVIOR:
            _glfw.hints.context.release = value;
            return;
        case GLFW_REFRESH_RATE:
            _glfw.hints.refreshRate = value;
            return;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window hint 0x%08X", hint);
}

void glfwDestroyWindow(GLFWwindow* handle)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;

    // Allow closing of NULL (to match the behavior of free)
    if (window == NULL)
        return;

    // Clear all callbacks to avoid exposing a half torn-down window object
    memset(&window->callbacks, 0, sizeof(window->callbacks));

    // The window's context must not be current on another thread when the
    // window is destroyed
    if (window == _glfwPlatformGetTls(&_glfw.contextSlot))
        glfwMakeContextCurrent(NULL);

    _glfw.platform.destroyWindow(window);

    // Unlink window from global linked list
    {
        _GLFWwindow** prev = &_glfw.windowListHead;

        while (*prev != window)
            prev = &(*prev)->next;

        *prev = window->next;
    }

    _glfw_free(window->title);
    _glfw_free(window);
}

void glfwSetWindowTitle(GLFWwindow* handle, const char* title)
{
    assert(title != NULL);

    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    char* prev = window->title;
    window->title = _glfw_strdup(title);

    _glfw.platform.setWindowTitle(window, title);
    _glfw_free(prev);
}

void glfwSetWindowIcon(GLFWwindow* handle, int count, const GLFWimage* images)
{
    assert(count >= 0);
    assert(count == 0 || images != NULL);

    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    if (count < 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid image count for window icon");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        assert(images[i].pixels != NULL);

        if (images[i].width <= 0 || images[i].height <= 0)
        {
            _glfwInputError(GLFW_INVALID_VALUE, "Invalid image dimensions for window icon");
            return;
        }
    }

    _glfw.platform.setWindowIcon(window, count, images);
}

void glfwSetWindowSize(GLFWwindow* handle, int width, int height)
{
    assert(width  >= 0);
    assert(height >= 0);

    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    window->videoMode.width  = width;
    window->videoMode.height = height;

    _glfw.platform.setWindowSize(window, width, height);
}

void glfwSetWindowAspectRatio(GLFWwindow* handle, int numer, int denom)
{
    assert(numer != 0);
    assert(denom != 0);

    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    if (numer != GLFW_DONT_CARE && denom != GLFW_DONT_CARE)
    {
        if (numer <= 0 || denom <= 0)
        {
            _glfwInputError(GLFW_INVALID_VALUE, "Invalid window aspect ratio %i:%i", numer, denom);
            return;
        }
    }

    window->numer = numer;
    window->denom = denom;

    if (window->monitor || !window->resizable)
        return;

    _glfw.platform.setWindowAspectRatio(window, numer, denom);
}

void glfwIconifyWindow(GLFWwindow* handle)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _glfw.platform.iconifyWindow(window);
}

void glfwRestoreWindow(GLFWwindow* handle)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _glfw.platform.restoreWindow(window);
}

void glfwMaximizeWindow(GLFWwindow* handle)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    if (window->monitor)
        return;

    _glfw.platform.maximizeWindow(window);
}

void glfwFocusWindow(GLFWwindow* handle)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _glfw.platform.focusWindow(window);
}

void glfwSetWindowAttrib(GLFWwindow* handle, int attrib, int value)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    value = value ? GLFW_TRUE : GLFW_FALSE;

    switch (attrib)
    {
        case GLFW_AUTO_ICONIFY:
            window->autoIconify = value;
            return;

        case GLFW_RESIZABLE:
            window->resizable = value;
            if (!window->monitor)
                _glfw.platform.setWindowResizable(window, value);
            return;

        case GLFW_DECORATED:
            window->decorated = value;
            if (!window->monitor)
                _glfw.platform.setWindowDecorated(window, value);
            return;

        case GLFW_FLOATING:
            window->floating = value;
            if (!window->monitor)
                _glfw.platform.setWindowFloating(window, value);
            return;

        case GLFW_MOUSE_PASSTHROUGH:
            window->mousePassthrough = value;
            _glfw.platform.setWindowMousePassthrough(window, value);
            return;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window attribute 0x%08X", attrib);
}

GLFWmonitor* glfwGetWindowMonitor(GLFWwindow* handle)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    return (GLFWmonitor*) window->monitor;
}

void glfwSetWindowMonitor(GLFWwindow* wh, GLFWmonitor* mh, int xpos, int ypos, int width, int height, int refreshRate)
{
    assert(width >= 0);
    assert(height >= 0);

    _GLFWwindow* window = (_GLFWwindow*) wh;
    _GLFWmonitor* monitor = (_GLFWmonitor*) mh;
    assert(window != NULL);

    if (width <= 0 || height <= 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid window size %ix%i", width, height);
        return;
    }

    if (refreshRate < 0 && refreshRate != GLFW_DONT_CARE)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid refresh rate %i", refreshRate);
        return;
    }

    window->videoMode.width       = width;
    window->videoMode.height      = height;
    window->videoMode.refreshRate = refreshRate;

    _glfw.platform.setWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate);
}

void glfwSetWindowSizeCallback(GLFWwindow* handle, GLFWwindowsizefun cbfun)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_SWAP(GLFWwindowsizefun, window->callbacks.size, cbfun);
}

void glfwSetWindowCloseCallback(GLFWwindow* handle, GLFWwindowclosefun cbfun)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;

    _GLFW_SWAP(GLFWwindowclosefun, window->callbacks.close, cbfun);
}

void glfwSetWindowRefreshCallback(GLFWwindow* handle, GLFWwindowrefreshfun cbfun)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_SWAP(GLFWwindowrefreshfun, window->callbacks.refresh, cbfun);
}

void glfwSetWindowFocusCallback(GLFWwindow* handle, GLFWwindowfocusfun cbfun)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_SWAP(GLFWwindowfocusfun, window->callbacks.focus, cbfun);
}

void glfwSetWindowIconifyCallback(GLFWwindow* handle, GLFWwindowiconifyfun cbfun)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_SWAP(GLFWwindowiconifyfun, window->callbacks.iconify, cbfun);
}

void glfwSetWindowMaximizeCallback(GLFWwindow* handle, GLFWwindowmaximizefun cbfun)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_SWAP(GLFWwindowmaximizefun, window->callbacks.maximize, cbfun);
}

void glfwSetFramebufferSizeCallback(GLFWwindow* handle, GLFWframebuffersizefun cbfun)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_SWAP(GLFWframebuffersizefun, window->callbacks.fbsize, cbfun);
}

void glfwPollEvents(void)
{
    _glfw.platform.pollEvents();
}