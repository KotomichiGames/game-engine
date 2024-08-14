/*************************************************************************
 * GLFW 3.5 - www.glfw.org
 * A library for OpenGL, window and input
 *------------------------------------------------------------------------
 * Copyright (c) 2002-2006 Marcus Geelnard
 * Copyright (c) 2006-2019 Camilla Löwy <elmindreda@glfw.org>
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

/*************************************************************************
 * Compiler- and platform-specific preprocessor work
 *************************************************************************/

/* If we are we on Windows, we want a single define for it.
 */
#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
 #define _WIN32
#endif /* _WIN32 */

#include <stdint.h>

/* The Vulkan header may have indirectly included windows.h (because of
 * VK_USE_PLATFORM_WIN32_KHR) so we offer our replacement symbols after it.
 */

/* It is customary to use APIENTRY for OpenGL function pointer declarations on
 * all platforms.  Additionally, the Windows OpenGL header needs APIENTRY.
 */
#if !defined(APIENTRY)
 #if defined(_WIN32)
  #define APIENTRY __stdcall
 #else
  #define APIENTRY
 #endif
 #define GLFW_APIENTRY_DEFINED
#endif /* APIENTRY */

/* Some Windows OpenGL headers need this.
 */
#if !defined(WINGDIAPI) && defined(_WIN32)
 #define WINGDIAPI __declspec(dllimport)
 #define GLFW_WINGDIAPI_DEFINED
#endif /* WINGDIAPI */

/* Some Windows GLU headers need this.
 */
#if !defined(CALLBACK) && defined(_WIN32)
 #define CALLBACK __stdcall
 #define GLFW_CALLBACK_DEFINED
#endif /* CALLBACK */

/* Include the chosen OpenGL or OpenGL ES headers.
 */
#if defined(GLFW_INCLUDE_ES1)

 #include <GLES/gl.h>
 #if defined(GLFW_INCLUDE_GLEXT)
  #include <GLES/glext.h>
 #endif

#elif defined(GLFW_INCLUDE_ES2)

 #include <GLES2/gl2.h>
 #if defined(GLFW_INCLUDE_GLEXT)
  #include <GLES2/gl2ext.h>
 #endif

#elif defined(GLFW_INCLUDE_ES3)

 #include <GLES3/gl3.h>
 #if defined(GLFW_INCLUDE_GLEXT)
  #include <GLES2/gl2ext.h>
 #endif

#elif defined(GLFW_INCLUDE_ES31)

 #include <GLES3/gl31.h>
 #if defined(GLFW_INCLUDE_GLEXT)
  #include <GLES2/gl2ext.h>
 #endif

#elif defined(GLFW_INCLUDE_ES32)

 #include <GLES3/gl32.h>
 #if defined(GLFW_INCLUDE_GLEXT)
  #include <GLES2/gl2ext.h>
 #endif

#elif defined(GLFW_INCLUDE_GLCOREARB)

 #if defined(__APPLE__)

  #include <OpenGL/gl3.h>
  #if defined(GLFW_INCLUDE_GLEXT)
   #include <OpenGL/gl3ext.h>
  #endif /*GLFW_INCLUDE_GLEXT*/

 #else /*__APPLE__*/

  #include <GL/glcorearb.h>
  #if defined(GLFW_INCLUDE_GLEXT)
   #include <GL/glext.h>
  #endif

 #endif /*__APPLE__*/

#elif defined(GLFW_INCLUDE_GLU)

 #if defined(__APPLE__)

  #if defined(GLFW_INCLUDE_GLU)
   #include <OpenGL/glu.h>
  #endif

 #else /*__APPLE__*/

  #if defined(GLFW_INCLUDE_GLU)
   #include <GL/glu.h>
  #endif

 #endif /*__APPLE__*/

#elif !defined(GLFW_INCLUDE_NONE) && \
      !defined(__gl_h_) && \
      !defined(__gles1_gl_h_) && \
      !defined(__gles2_gl2_h_) && \
      !defined(__gles2_gl3_h_) && \
      !defined(__gles2_gl31_h_) && \
      !defined(__gles2_gl32_h_) && \
      !defined(__gl_glcorearb_h_) && \
      !defined(__gl2_h_) /*legacy*/ && \
      !defined(__gl3_h_) /*legacy*/ && \
      !defined(__gl31_h_) /*legacy*/ && \
      !defined(__gl32_h_) /*legacy*/ && \
      !defined(__glcorearb_h_) /*legacy*/ && \
      !defined(__GL_H__) /*non-standard*/ && \
      !defined(__gltypes_h_) /*non-standard*/ && \
      !defined(__glee_h_) /*non-standard*/

 #if defined(__APPLE__)

  #if !defined(GLFW_INCLUDE_GLEXT)
   #define GL_GLEXT_LEGACY
  #endif
  #include <OpenGL/gl.h>

 #else /*__APPLE__*/

  #include <GL/gl.h>
  #if defined(GLFW_INCLUDE_GLEXT)
   #include <GL/glext.h>
  #endif

 #endif /*__APPLE__*/

#endif /* OpenGL and OpenGL ES headers */

#if defined(GLFW_DLL) && defined(_GLFW_BUILD_DLL)
 /* GLFW_DLL must be defined by applications that are linking against the DLL
  * version of the GLFW library.  _GLFW_BUILD_DLL is defined by the GLFW
  * configuration header when compiling the DLL version of the library.
  */
 #error "You must not have both GLFW_DLL and _GLFW_BUILD_DLL defined"
#endif

/* GLFWAPI is used to declare public API functions for export
 * from the DLL / shared library / dynamic library.
 */
#if defined(_WIN32) && defined(_GLFW_BUILD_DLL)
 /* We are building GLFW as a Win32 DLL */
 #define GLFWAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(GLFW_DLL)
 /* We are calling a GLFW Win32 DLL */
 #define GLFWAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(_GLFW_BUILD_DLL)
 /* We are building GLFW as a Unix shared library */
 #define GLFWAPI __attribute__((visibility("default")))
#else
 #define GLFWAPI
#endif

/*************************************************************************
 * GLFW API tokens
 *************************************************************************/

#define GLFW_TRUE                   1
#define GLFW_FALSE                  0

#define GLFW_RELEASE                0
#define GLFW_PRESS                  1
#define GLFW_REPEAT                 2

#define GLFW_KEY_UNKNOWN            -1

/* Printable keys */
#define GLFW_KEY_SPACE              32
#define GLFW_KEY_APOSTROPHE         39  /* ' */
#define GLFW_KEY_COMMA              44  /* , */
#define GLFW_KEY_MINUS              45  /* - */
#define GLFW_KEY_PERIOD             46  /* . */
#define GLFW_KEY_SLASH              47  /* / */
#define GLFW_KEY_0                  48
#define GLFW_KEY_1                  49
#define GLFW_KEY_2                  50
#define GLFW_KEY_3                  51
#define GLFW_KEY_4                  52
#define GLFW_KEY_5                  53
#define GLFW_KEY_6                  54
#define GLFW_KEY_7                  55
#define GLFW_KEY_8                  56
#define GLFW_KEY_9                  57
#define GLFW_KEY_SEMICOLON          59  /* ; */
#define GLFW_KEY_EQUAL              61  /* = */
#define GLFW_KEY_A                  65
#define GLFW_KEY_B                  66
#define GLFW_KEY_C                  67
#define GLFW_KEY_D                  68
#define GLFW_KEY_E                  69
#define GLFW_KEY_F                  70
#define GLFW_KEY_G                  71
#define GLFW_KEY_H                  72
#define GLFW_KEY_I                  73
#define GLFW_KEY_J                  74
#define GLFW_KEY_K                  75
#define GLFW_KEY_L                  76
#define GLFW_KEY_M                  77
#define GLFW_KEY_N                  78
#define GLFW_KEY_O                  79
#define GLFW_KEY_P                  80
#define GLFW_KEY_Q                  81
#define GLFW_KEY_R                  82
#define GLFW_KEY_S                  83
#define GLFW_KEY_T                  84
#define GLFW_KEY_U                  85
#define GLFW_KEY_V                  86
#define GLFW_KEY_W                  87
#define GLFW_KEY_X                  88
#define GLFW_KEY_Y                  89
#define GLFW_KEY_Z                  90
#define GLFW_KEY_LEFT_BRACKET       91  /* [ */
#define GLFW_KEY_BACKSLASH          92  /* \ */
#define GLFW_KEY_RIGHT_BRACKET      93  /* ] */
#define GLFW_KEY_GRAVE_ACCENT       96  /* ` */
#define GLFW_KEY_WORLD_1            161 /* non-US #1 */
#define GLFW_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define GLFW_KEY_ESCAPE             256
#define GLFW_KEY_ENTER              257
#define GLFW_KEY_TAB                258
#define GLFW_KEY_BACKSPACE          259
#define GLFW_KEY_INSERT             260
#define GLFW_KEY_DELETE             261
#define GLFW_KEY_RIGHT              262
#define GLFW_KEY_LEFT               263
#define GLFW_KEY_DOWN               264
#define GLFW_KEY_UP                 265
#define GLFW_KEY_PAGE_UP            266
#define GLFW_KEY_PAGE_DOWN          267
#define GLFW_KEY_HOME               268
#define GLFW_KEY_END                269
#define GLFW_KEY_CAPS_LOCK          280
#define GLFW_KEY_SCROLL_LOCK        281
#define GLFW_KEY_NUM_LOCK           282
#define GLFW_KEY_PRINT_SCREEN       283
#define GLFW_KEY_PAUSE              284
#define GLFW_KEY_F1                 290
#define GLFW_KEY_F2                 291
#define GLFW_KEY_F3                 292
#define GLFW_KEY_F4                 293
#define GLFW_KEY_F5                 294
#define GLFW_KEY_F6                 295
#define GLFW_KEY_F7                 296
#define GLFW_KEY_F8                 297
#define GLFW_KEY_F9                 298
#define GLFW_KEY_F10                299
#define GLFW_KEY_F11                300
#define GLFW_KEY_F12                301
#define GLFW_KEY_KP_0               320
#define GLFW_KEY_KP_1               321
#define GLFW_KEY_KP_2               322
#define GLFW_KEY_KP_3               323
#define GLFW_KEY_KP_4               324
#define GLFW_KEY_KP_5               325
#define GLFW_KEY_KP_6               326
#define GLFW_KEY_KP_7               327
#define GLFW_KEY_KP_8               328
#define GLFW_KEY_KP_9               329
#define GLFW_KEY_KP_DECIMAL         330
#define GLFW_KEY_KP_DIVIDE          331
#define GLFW_KEY_KP_MULTIPLY        332
#define GLFW_KEY_KP_SUBTRACT        333
#define GLFW_KEY_KP_ADD             334
#define GLFW_KEY_KP_ENTER           335
#define GLFW_KEY_KP_EQUAL           336
#define GLFW_KEY_LEFT_SHIFT         340
#define GLFW_KEY_LEFT_CONTROL       341
#define GLFW_KEY_LEFT_ALT           342
#define GLFW_KEY_LEFT_SUPER         343
#define GLFW_KEY_RIGHT_SHIFT        344
#define GLFW_KEY_RIGHT_CONTROL      345
#define GLFW_KEY_RIGHT_ALT          346
#define GLFW_KEY_RIGHT_SUPER        347
#define GLFW_KEY_MENU               348

#define GLFW_KEY_LAST               GLFW_KEY_MENU

#define GLFW_MOD_SHIFT           0x0001
#define GLFW_MOD_CONTROL         0x0002
#define GLFW_MOD_ALT             0x0004
#define GLFW_MOD_SUPER           0x0008
#define GLFW_MOD_CAPS_LOCK       0x0010
#define GLFW_MOD_NUM_LOCK        0x0020

#define GLFW_MOUSE_BUTTON_1         0
#define GLFW_MOUSE_BUTTON_2         1
#define GLFW_MOUSE_BUTTON_3         2
#define GLFW_MOUSE_BUTTON_4         3
#define GLFW_MOUSE_BUTTON_5         4
#define GLFW_MOUSE_BUTTON_6         5
#define GLFW_MOUSE_BUTTON_7         6
#define GLFW_MOUSE_BUTTON_8         7
#define GLFW_MOUSE_BUTTON_LAST      GLFW_MOUSE_BUTTON_8
#define GLFW_MOUSE_BUTTON_LEFT      GLFW_MOUSE_BUTTON_1
#define GLFW_MOUSE_BUTTON_RIGHT     GLFW_MOUSE_BUTTON_2
#define GLFW_MOUSE_BUTTON_MIDDLE    GLFW_MOUSE_BUTTON_3

#define GLFW_NO_ERROR               0
#define GLFW_NOT_INITIALIZED        0x00010001
#define GLFW_NO_CURRENT_CONTEXT     0x00010002
#define GLFW_INVALID_ENUM           0x00010003
#define GLFW_INVALID_VALUE          0x00010004
#define GLFW_OUT_OF_MEMORY          0x00010005
#define GLFW_API_UNAVAILABLE        0x00010006
#define GLFW_VERSION_UNAVAILABLE    0x00010007
#define GLFW_PLATFORM_ERROR         0x00010008
#define GLFW_FORMAT_UNAVAILABLE     0x00010009
#define GLFW_NO_WINDOW_CONTEXT      0x0001000A
#define GLFW_CURSOR_UNAVAILABLE     0x0001000B
#define GLFW_FEATURE_UNAVAILABLE    0x0001000C
#define GLFW_FEATURE_UNIMPLEMENTED  0x0001000D
#define GLFW_PLATFORM_UNAVAILABLE   0x0001000E

#define GLFW_FOCUSED                0x00020001
#define GLFW_ICONIFIED              0x00020002
#define GLFW_RESIZABLE              0x00020003
#define GLFW_VISIBLE                0x00020004
#define GLFW_DECORATED              0x00020005
#define GLFW_AUTO_ICONIFY           0x00020006
#define GLFW_FLOATING               0x00020007
#define GLFW_MAXIMIZED              0x00020008
#define GLFW_CENTER_CURSOR          0x00020009
#define GLFW_HOVERED                0x0002000B
#define GLFW_FOCUS_ON_SHOW          0x0002000C

#define GLFW_MOUSE_PASSTHROUGH      0x0002000D
#define GLFW_POSITION_X             0x0002000E
#define GLFW_POSITION_Y             0x0002000F
#define GLFW_RED_BITS               0x00021001
#define GLFW_GREEN_BITS             0x00021002
#define GLFW_BLUE_BITS              0x00021003
#define GLFW_ALPHA_BITS             0x00021004
#define GLFW_DEPTH_BITS             0x00021005
#define GLFW_STENCIL_BITS           0x00021006
#define GLFW_AUX_BUFFERS            0x0002100B
#define GLFW_STEREO                 0x0002100C
#define GLFW_SAMPLES                0x0002100D
#define GLFW_SRGB_CAPABLE           0x0002100E
#define GLFW_REFRESH_RATE           0x0002100F
#define GLFW_DOUBLEBUFFER           0x00021010

#define GLFW_CLIENT_API             0x00022001
#define GLFW_CONTEXT_ROBUSTNESS     0x00022005
#define GLFW_OPENGL_PROFILE         0x00022008
#define GLFW_CONTEXT_RELEASE_BEHAVIOR 0x00022009
#define GLFW_CONTEXT_NO_ERROR       0x0002200A
#define GLFW_CONTEXT_CREATION_API   0x0002200B
#define GLFW_SCALE_TO_MONITOR       0x0002200C
#define GLFW_SCALE_FRAMEBUFFER      0x0002200D

#define GLFW_NO_API                          0
#define GLFW_OPENGL_API             0x00030001

#define GLFW_NO_ROBUSTNESS                   0
#define GLFW_NO_RESET_NOTIFICATION  0x00031001
#define GLFW_LOSE_CONTEXT_ON_RESET  0x00031002

#define GLFW_OPENGL_ANY_PROFILE              0
#define GLFW_OPENGL_CORE_PROFILE    0x00032001

#define GLFW_CURSOR                  0x00033001
#define GLFW_STICKY_KEYS             0x00033002
#define GLFW_STICKY_MOUSE_BUTTONS    0x00033003
#define GLFW_LOCK_KEY_MODS           0x00033004
#define GLFW_RAW_MOUSE_MOTION        0x00033005
#define GLFW_UNLIMITED_MOUSE_BUTTONS 0x00033006

#define GLFW_CURSOR_NORMAL          0x00034001
#define GLFW_CURSOR_HIDDEN          0x00034002
#define GLFW_CURSOR_DISABLED        0x00034003
#define GLFW_CURSOR_CAPTURED        0x00034004

#define GLFW_ANY_RELEASE_BEHAVIOR            0
#define GLFW_RELEASE_BEHAVIOR_FLUSH 0x00035001
#define GLFW_RELEASE_BEHAVIOR_NONE  0x00035002

#define GLFW_NATIVE_CONTEXT_API     0x00036001

#define GLFW_ANY_POSITION           0x80000000

#define GLFW_ARROW_CURSOR           0x00036001
#define GLFW_IBEAM_CURSOR           0x00036002
#define GLFW_CROSSHAIR_CURSOR       0x00036003
#define GLFW_POINTING_HAND_CURSOR   0x00036004
#define GLFW_RESIZE_EW_CURSOR       0x00036005
#define GLFW_RESIZE_NS_CURSOR       0x00036006
#define GLFW_RESIZE_NWSE_CURSOR     0x00036007
#define GLFW_RESIZE_NESW_CURSOR     0x00036008
#define GLFW_RESIZE_ALL_CURSOR      0x00036009
#define GLFW_NOT_ALLOWED_CURSOR     0x0003600A
#define GLFW_HRESIZE_CURSOR         GLFW_RESIZE_EW_CURSOR
#define GLFW_VRESIZE_CURSOR         GLFW_RESIZE_NS_CURSOR
#define GLFW_HAND_CURSOR            GLFW_POINTING_HAND_CURSOR

#define GLFW_CONNECTED              0x00040001
#define GLFW_DISCONNECTED           0x00040002

#define GLFW_PLATFORM               0x00050003
#define GLFW_ANY_PLATFORM           0x00060000
#define GLFW_PLATFORM_WIN32         0x00060001

#define GLFW_DONT_CARE              -1

/*************************************************************************
 * GLFW API types
 *************************************************************************/

typedef void (*GLFWglproc)(void);

typedef struct GLFWmonitor GLFWmonitor;
typedef struct GLFWwindow  GLFWwindow;
typedef struct GLFWcursor  GLFWcursor;

typedef void* (* GLFWallocatefun)(size_t size, void* user);
typedef void* (* GLFWreallocatefun)(void* block, size_t size, void* user);
typedef void  (* GLFWdeallocatefun)(void* block, void* user);
typedef void (* GLFWwindowposfun)(GLFWwindow* window, int xpos, int ypos);
typedef void (* GLFWwindowsizefun)(GLFWwindow* window, int width, int height);
typedef void (* GLFWwindowclosefun)(GLFWwindow* window);
typedef void (* GLFWwindowrefreshfun)(GLFWwindow* window);
typedef void (* GLFWwindowfocusfun)(GLFWwindow* window, int focused);
typedef void (* GLFWwindowiconifyfun)(GLFWwindow* window, int iconified);
typedef void (* GLFWwindowmaximizefun)(GLFWwindow* window, int maximized);
typedef void (* GLFWframebuffersizefun)(GLFWwindow* window, int width, int height);
typedef void (* GLFWwindowcontentscalefun)(GLFWwindow* window, float xscale, float yscale);
typedef void (* GLFWmousebuttonfun)(GLFWwindow* window, int button, int action, int mods);
typedef void (* GLFWcursorposfun)(GLFWwindow* window, double xpos, double ypos);
typedef void (* GLFWcursorenterfun)(GLFWwindow* window, int entered);
typedef void (* GLFWscrollfun)(GLFWwindow* window, double xoffset, double yoffset);
typedef void (* GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);
typedef void (* GLFWcharfun)(GLFWwindow* window, unsigned int codepoint);
typedef void (* GLFWcharmodsfun)(GLFWwindow* window, unsigned int codepoint, int mods);
typedef void (* GLFWdropfun)(GLFWwindow* window, int path_count, const char* paths[]);
typedef void (* GLFWmonitorfun)(GLFWmonitor* monitor, int event);

typedef struct GLFWvidmode
{
    int width;
    int height;
    int redBits;
    int greenBits;
    int blueBits;
    int refreshRate;
} GLFWvidmode;

typedef struct GLFWgammaramp
{
    unsigned short* red;
    unsigned short* green;
    unsigned short* blue;
    unsigned int size;
} GLFWgammaramp;

typedef struct GLFWimage
{
    int width;
    int height;
    unsigned char* pixels;
} GLFWimage;

/*************************************************************************
 * GLFW API functions
 *************************************************************************/

GLFWAPI int  glfwInit(void);
GLFWAPI void glfwTerminate(void);

GLFWAPI void glfwInitHint(int hint, int value);
GLFWAPI int glfwGetPlatform(void);

GLFWAPI int glfwPlatformSupported(int platform);
GLFWAPI GLFWmonitor** glfwGetMonitors(int* count);

GLFWAPI GLFWmonitor* glfwGetPrimaryMonitor(void);
GLFWAPI void glfwGetMonitorPos(GLFWmonitor* monitor, int* xpos, int* ypos);

GLFWAPI void glfwGetMonitorWorkarea(GLFWmonitor* monitor, int* xpos, int* ypos, int* width, int* height);
GLFWAPI void glfwGetMonitorPhysicalSize(GLFWmonitor* monitor, int* widthMM, int* heightMM);

GLFWAPI void glfwGetMonitorContentScale(GLFWmonitor* monitor, float* xscale, float* yscale);
GLFWAPI const char* glfwGetMonitorName(GLFWmonitor* monitor);

GLFWAPI void glfwSetMonitorUserPointer(GLFWmonitor* monitor, void* pointer);
GLFWAPI void* glfwGetMonitorUserPointer(GLFWmonitor* monitor);

GLFWAPI GLFWmonitorfun glfwSetMonitorCallback(GLFWmonitorfun callback);
GLFWAPI const GLFWvidmode* glfwGetVideoModes(GLFWmonitor* monitor, int* count);
GLFWAPI const GLFWvidmode* glfwGetVideoMode(GLFWmonitor* monitor);

GLFWAPI void glfwSetGamma(GLFWmonitor* monitor, float gamma);
GLFWAPI const GLFWgammaramp* glfwGetGammaRamp(GLFWmonitor* monitor);

GLFWAPI void glfwSetGammaRamp(GLFWmonitor* monitor, const GLFWgammaramp* ramp);

GLFWAPI void glfwDefaultWindowHints(void);
GLFWAPI void glfwWindowHint(int hint, int value);

GLFWAPI GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor);

GLFWAPI void glfwDestroyWindow(GLFWwindow* window);
GLFWAPI int glfwWindowShouldClose(GLFWwindow* window);

GLFWAPI void glfwSetWindowShouldClose(GLFWwindow* window, int value);
GLFWAPI const char* glfwGetWindowTitle(GLFWwindow* window);

GLFWAPI void glfwSetWindowTitle(GLFWwindow* window, const char* title);
GLFWAPI void glfwSetWindowIcon(GLFWwindow* window, int count, const GLFWimage* images);

GLFWAPI void glfwGetWindowPos(GLFWwindow* window, int* xpos, int* ypos);
GLFWAPI void glfwSetWindowPos(GLFWwindow* window, int xpos, int ypos);

/*! @brief Retrieves the size of the content area of the specified window.
 *
 *  This function retrieves the size, in screen coordinates, of the content area
 *  of the specified window.  If you wish to retrieve the size of the
 *  framebuffer of the window in pixels, see @ref glfwGetFramebufferSize.
 *
 *  Any or all of the size arguments may be `NULL`.  If an error occurs, all
 *  non-`NULL` size arguments will be set to zero.
 *
 *  @param[in] window The window whose size to retrieve.
 *  @param[out] width Where to store the width, in screen coordinates, of the
 *  content area, or `NULL`.
 *  @param[out] height Where to store the height, in screen coordinates, of the
 *  content area, or `NULL`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_size
 *  @sa @ref glfwSetWindowSize
 *
 *  @since Added in version 1.0.
 *  @glfw3 Added window handle parameter.
 *
 *  @ingroup window
 */
GLFWAPI void glfwGetWindowSize(GLFWwindow* window, int* width, int* height);

/*! @brief Sets the size limits of the specified window.
 *
 *  This function sets the size limits of the content area of the specified
 *  window.  If the window is full screen, the size limits only take effect
 *  once it is made windowed.  If the window is not resizable, this function
 *  does nothing.
 *
 *  The size limits are applied immediately to a windowed mode window and may
 *  cause it to be resized.
 *
 *  The maximum dimensions must be greater than or equal to the minimum
 *  dimensions and all must be greater than or equal to zero.
 *
 *  @param[in] window The window to set limits for.
 *  @param[in] minwidth The minimum width, in screen coordinates, of the content
 *  area, or `GLFW_DONT_CARE`.
 *  @param[in] minheight The minimum height, in screen coordinates, of the
 *  content area, or `GLFW_DONT_CARE`.
 *  @param[in] maxwidth The maximum width, in screen coordinates, of the content
 *  area, or `GLFW_DONT_CARE`.
 *  @param[in] maxheight The maximum height, in screen coordinates, of the
 *  content area, or `GLFW_DONT_CARE`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_VALUE and @ref GLFW_PLATFORM_ERROR.
 *
 *  @remark If you set size limits and an aspect ratio that conflict, the
 *  results are undefined.
 *
 *  @remark @wayland The size limits will not be applied until the window is
 *  actually resized, either by the user or by the compositor.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_sizelimits
 *  @sa @ref glfwSetWindowAspectRatio
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup window
 */
GLFWAPI void glfwSetWindowSizeLimits(GLFWwindow* window, int minwidth, int minheight, int maxwidth, int maxheight);

/*! @brief Sets the aspect ratio of the specified window.
 *
 *  This function sets the required aspect ratio of the content area of the
 *  specified window.  If the window is full screen, the aspect ratio only takes
 *  effect once it is made windowed.  If the window is not resizable, this
 *  function does nothing.
 *
 *  The aspect ratio is specified as a numerator and a denominator and both
 *  values must be greater than zero.  For example, the common 16:9 aspect ratio
 *  is specified as 16 and 9, respectively.
 *
 *  If the numerator and denominator is set to `GLFW_DONT_CARE` then the aspect
 *  ratio limit is disabled.
 *
 *  The aspect ratio is applied immediately to a windowed mode window and may
 *  cause it to be resized.
 *
 *  @param[in] window The window to set limits for.
 *  @param[in] numer The numerator of the desired aspect ratio, or
 *  `GLFW_DONT_CARE`.
 *  @param[in] denom The denominator of the desired aspect ratio, or
 *  `GLFW_DONT_CARE`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_VALUE and @ref GLFW_PLATFORM_ERROR.
 *
 *  @remark If you set size limits and an aspect ratio that conflict, the
 *  results are undefined.
 *
 *  @remark @wayland The aspect ratio will not be applied until the window is
 *  actually resized, either by the user or by the compositor.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_sizelimits
 *  @sa @ref glfwSetWindowSizeLimits
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup window
 */
GLFWAPI void glfwSetWindowAspectRatio(GLFWwindow* window, int numer, int denom);

/*! @brief Sets the size of the content area of the specified window.
 *
 *  This function sets the size, in screen coordinates, of the content area of
 *  the specified window.
 *
 *  For full screen windows, this function updates the resolution of its desired
 *  video mode and switches to the video mode closest to it, without affecting
 *  the window's context.  As the context is unaffected, the bit depths of the
 *  framebuffer remain unchanged.
 *
 *  If you wish to update the refresh rate of the desired video mode in addition
 *  to its resolution, see @ref glfwSetWindowMonitor.
 *
 *  The window manager may put limits on what sizes are allowed.  GLFW cannot
 *  and should not override these limits.
 *
 *  @param[in] window The window to resize.
 *  @param[in] width The desired width, in screen coordinates, of the window
 *  content area.
 *  @param[in] height The desired height, in screen coordinates, of the window
 *  content area.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_size
 *  @sa @ref glfwGetWindowSize
 *  @sa @ref glfwSetWindowMonitor
 *
 *  @since Added in version 1.0.
 *  @glfw3 Added window handle parameter.
 *
 *  @ingroup window
 */
GLFWAPI void glfwSetWindowSize(GLFWwindow* window, int width, int height);

/*! @brief Retrieves the size of the framebuffer of the specified window.
 *
 *  This function retrieves the size, in pixels, of the framebuffer of the
 *  specified window.  If you wish to retrieve the size of the window in screen
 *  coordinates, see @ref glfwGetWindowSize.
 *
 *  Any or all of the size arguments may be `NULL`.  If an error occurs, all
 *  non-`NULL` size arguments will be set to zero.
 *
 *  @param[in] window The window whose framebuffer to query.
 *  @param[out] width Where to store the width, in pixels, of the framebuffer,
 *  or `NULL`.
 *  @param[out] height Where to store the height, in pixels, of the framebuffer,
 *  or `NULL`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_fbsize
 *  @sa @ref glfwSetFramebufferSizeCallback
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI void glfwGetFramebufferSize(GLFWwindow* window, int* width, int* height);

/*! @brief Retrieves the size of the frame of the window.
 *
 *  This function retrieves the size, in screen coordinates, of each edge of the
 *  frame of the specified window.  This size includes the title bar, if the
 *  window has one.  The size of the frame may vary depending on the
 *  [window-related hints](@ref window_hints_wnd) used to create it.
 *
 *  Because this function retrieves the size of each window frame edge and not
 *  the offset along a particular coordinate axis, the retrieved values will
 *  always be zero or positive.
 *
 *  Any or all of the size arguments may be `NULL`.  If an error occurs, all
 *  non-`NULL` size arguments will be set to zero.
 *
 *  @param[in] window The window whose frame size to query.
 *  @param[out] left Where to store the size, in screen coordinates, of the left
 *  edge of the window frame, or `NULL`.
 *  @param[out] top Where to store the size, in screen coordinates, of the top
 *  edge of the window frame, or `NULL`.
 *  @param[out] right Where to store the size, in screen coordinates, of the
 *  right edge of the window frame, or `NULL`.
 *  @param[out] bottom Where to store the size, in screen coordinates, of the
 *  bottom edge of the window frame, or `NULL`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_size
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup window
 */
GLFWAPI void glfwGetWindowFrameSize(GLFWwindow* window, int* left, int* top, int* right, int* bottom);

/*! @brief Retrieves the content scale for the specified window.
 *
 *  This function retrieves the content scale for the specified window.  The
 *  content scale is the ratio between the current DPI and the platform's
 *  default DPI.  This is especially important for text and any UI elements.  If
 *  the pixel dimensions of your UI scaled by this look appropriate on your
 *  machine then it should appear at a reasonable size on other machines
 *  regardless of their DPI and scaling settings.  This relies on the system DPI
 *  and scaling settings being somewhat correct.
 *
 *  On platforms where each monitors can have its own content scale, the window
 *  content scale will depend on which monitor the system considers the window
 *  to be on.
 *
 *  @param[in] window The window to query.
 *  @param[out] xscale Where to store the x-axis content scale, or `NULL`.
 *  @param[out] yscale Where to store the y-axis content scale, or `NULL`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_scale
 *  @sa @ref glfwSetWindowContentScaleCallback
 *  @sa @ref glfwGetMonitorContentScale
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup window
 */
GLFWAPI void glfwGetWindowContentScale(GLFWwindow* window, float* xscale, float* yscale);

/*! @brief Returns the opacity of the whole window.
 *
 *  This function returns the opacity of the window, including any decorations.
 *
 *  The opacity (or alpha) value is a positive finite number between zero and
 *  one, where zero is fully transparent and one is fully opaque.  If the system
 *  does not support whole window transparency, this function always returns one.
 *
 *  The initial opacity value for newly created windows is one.
 *
 *  @param[in] window The window to query.
 *  @return The opacity value of the specified window.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_transparency
 *  @sa @ref glfwSetWindowOpacity
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup window
 */
GLFWAPI float glfwGetWindowOpacity(GLFWwindow* window);

/*! @brief Sets the opacity of the whole window.
 *
 *  This function sets the opacity of the window, including any decorations.
 *
 *  The opacity (or alpha) value is a positive finite number between zero and
 *  one, where zero is fully transparent and one is fully opaque.
 *
 *  The initial opacity value for newly created windows is one.
 *
 *  A window created with framebuffer transparency may not use whole window
 *  transparency.  The results of doing this are undefined.
 *
 *  @param[in] window The window to set the opacity for.
 *  @param[in] opacity The desired opacity of the specified window.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_PLATFORM_ERROR and @ref GLFW_FEATURE_UNAVAILABLE (see remarks).
 *
 *  @remark @wayland There is no way to set an opacity factor for a window.
 *  This function will emit @ref GLFW_FEATURE_UNAVAILABLE.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_transparency
 *  @sa @ref glfwGetWindowOpacity
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup window
 */
GLFWAPI void glfwSetWindowOpacity(GLFWwindow* window, float opacity);

/*! @brief Iconifies the specified window.
 *
 *  This function iconifies (minimizes) the specified window if it was
 *  previously restored.  If the window is already iconified, this function does
 *  nothing.
 *
 *  If the specified window is a full screen window, GLFW restores the original
 *  video mode of the monitor.  The window's desired video mode is set again
 *  when the window is restored.
 *
 *  @param[in] window The window to iconify.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @remark @wayland Once a window is iconified, @ref glfwRestoreWindow won’t
 *  be able to restore it.  This is a design decision of the xdg-shell
 *  protocol.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_iconify
 *  @sa @ref glfwRestoreWindow
 *  @sa @ref glfwMaximizeWindow
 *
 *  @since Added in version 2.1.
 *  @glfw3 Added window handle parameter.
 *
 *  @ingroup window
 */
GLFWAPI void glfwIconifyWindow(GLFWwindow* window);

/*! @brief Restores the specified window.
 *
 *  This function restores the specified window if it was previously iconified
 *  (minimized) or maximized.  If the window is already restored, this function
 *  does nothing.
 *
 *  If the specified window is an iconified full screen window, its desired
 *  video mode is set again for its monitor when the window is restored.
 *
 *  @param[in] window The window to restore.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_iconify
 *  @sa @ref glfwIconifyWindow
 *  @sa @ref glfwMaximizeWindow
 *
 *  @since Added in version 2.1.
 *  @glfw3 Added window handle parameter.
 *
 *  @ingroup window
 */
GLFWAPI void glfwRestoreWindow(GLFWwindow* window);

/*! @brief Maximizes the specified window.
 *
 *  This function maximizes the specified window if it was previously not
 *  maximized.  If the window is already maximized, this function does nothing.
 *
 *  If the specified window is a full screen window, this function does nothing.
 *
 *  @param[in] window The window to maximize.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @par Thread Safety
 *  This function may only be called from the main thread.
 *
 *  @sa @ref window_iconify
 *  @sa @ref glfwIconifyWindow
 *  @sa @ref glfwRestoreWindow
 *
 *  @since Added in GLFW 3.2.
 *
 *  @ingroup window
 */
GLFWAPI void glfwMaximizeWindow(GLFWwindow* window);

/*! @brief Makes the specified window visible.
 *
 *  This function makes the specified window visible if it was previously
 *  hidden.  If the window is already visible or is in full screen mode, this
 *  function does nothing.
 *
 *  By default, windowed mode windows are focused when shown
 *  Set the [GLFW_FOCUS_ON_SHOW](@ref GLFW_FOCUS_ON_SHOW_hint) window hint
 *  to change this behavior for all newly created windows, or change the
 *  behavior for an existing window with @ref glfwSetWindowAttrib.
 *
 *  @param[in] window The window to make visible.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @remark @wayland Because Wayland wants every frame of the desktop to be
 *  complete, this function does not immediately make the window visible.
 *  Instead it will become visible the next time the window framebuffer is
 *  updated after this call.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_hide
 *  @sa @ref glfwHideWindow
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI void glfwShowWindow(GLFWwindow* window);

/*! @brief Hides the specified window.
 *
 *  This function hides the specified window if it was previously visible.  If
 *  the window is already hidden or is in full screen mode, this function does
 *  nothing.
 *
 *  @param[in] window The window to hide.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_hide
 *  @sa @ref glfwShowWindow
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI void glfwHideWindow(GLFWwindow* window);

/*! @brief Brings the specified window to front and sets input focus.
 *
 *  This function brings the specified window to front and sets input focus.
 *  The window should already be visible and not iconified.
 *
 *  By default, both windowed and full screen mode windows are focused when
 *  initially created.  Set the [GLFW_FOCUSED](@ref GLFW_FOCUSED_hint) to
 *  disable this behavior.
 *
 *  Also by default, windowed mode windows are focused when shown
 *  with @ref glfwShowWindow. Set the
 *  [GLFW_FOCUS_ON_SHOW](@ref GLFW_FOCUS_ON_SHOW_hint) to disable this behavior.
 *
 *  __Do not use this function__ to steal focus from other applications unless
 *  you are certain that is what the user wants.  Focus stealing can be
 *  extremely disruptive.
 *
 *  For a less disruptive way of getting the user's attention, see
 *  [attention requests](@ref window_attention).
 *
 *  @param[in] window The window to give input focus.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @remark @wayland The compositor will likely ignore focus requests unless
 *  another window created by the same application already has input focus.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_focus
 *  @sa @ref window_attention
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup window
 */
GLFWAPI void glfwFocusWindow(GLFWwindow* window);

GLFWAPI GLFWmonitor* glfwGetWindowMonitor(GLFWwindow* window);
GLFWAPI void glfwSetWindowMonitor(GLFWwindow* window, GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);

GLFWAPI void glfwSetWindowAttrib(GLFWwindow* window, int attrib, int value);
GLFWAPI void glfwSetWindowUserPointer(GLFWwindow* window, void* pointer);
GLFWAPI void* glfwGetWindowUserPointer(GLFWwindow* window);

GLFWAPI GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow* window, GLFWwindowposfun callback);
GLFWAPI GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback);
GLFWAPI GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindow* window, GLFWwindowclosefun callback);
GLFWAPI GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow* window, GLFWwindowrefreshfun callback);
GLFWAPI GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindow* window, GLFWwindowfocusfun callback);
GLFWAPI GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindow* window, GLFWwindowiconifyfun callback);
GLFWAPI GLFWwindowmaximizefun glfwSetWindowMaximizeCallback(GLFWwindow* window, GLFWwindowmaximizefun callback);
GLFWAPI GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun callback);
GLFWAPI GLFWwindowcontentscalefun glfwSetWindowContentScaleCallback(GLFWwindow* window, GLFWwindowcontentscalefun callback);

GLFWAPI void glfwPollEvents(void);

GLFWAPI int glfwGetInputMode(GLFWwindow* window, int mode);
GLFWAPI void glfwSetInputMode(GLFWwindow* window, int mode, int value);
GLFWAPI int glfwRawMouseMotionSupported(void);
GLFWAPI const char* glfwGetKeyName(int key, int scancode);

GLFWAPI int glfwGetKeyScancode(int key);

GLFWAPI int glfwGetKey(GLFWwindow* window, int key);
GLFWAPI int glfwGetMouseButton(GLFWwindow* window, int button);
GLFWAPI void glfwGetCursorPos(GLFWwindow* window, double* xpos, double* ypos);
GLFWAPI void glfwSetCursorPos(GLFWwindow* window, double xpos, double ypos);
GLFWAPI GLFWcursor* glfwCreateCursor(const GLFWimage* image, int xhot, int yhot);
GLFWAPI GLFWcursor* glfwCreateStandardCursor(int shape);
GLFWAPI void glfwDestroyCursor(GLFWcursor* cursor);
GLFWAPI void glfwSetCursor(GLFWwindow* window, GLFWcursor* cursor);
GLFWAPI GLFWkeyfun glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun callback);
GLFWAPI GLFWcharfun glfwSetCharCallback(GLFWwindow* window, GLFWcharfun callback);
GLFWAPI GLFWcharmodsfun glfwSetCharModsCallback(GLFWwindow* window, GLFWcharmodsfun callback);
GLFWAPI GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWwindow* window, GLFWmousebuttonfun callback);
GLFWAPI GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);
GLFWAPI GLFWcursorenterfun glfwSetCursorEnterCallback(GLFWwindow* window, GLFWcursorenterfun callback);
GLFWAPI GLFWscrollfun glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun callback);
GLFWAPI GLFWdropfun glfwSetDropCallback(GLFWwindow* window, GLFWdropfun callback);

GLFWAPI void glfwSetClipboardString(GLFWwindow* window, const char* string);
GLFWAPI const char* glfwGetClipboardString(GLFWwindow* window);

GLFWAPI double glfwGetTime(void);
GLFWAPI void glfwSetTime(double time);
GLFWAPI uint64_t glfwGetTimerValue(void);
GLFWAPI uint64_t glfwGetTimerFrequency(void);

GLFWAPI void glfwMakeContextCurrent(GLFWwindow* window);

GLFWAPI void glfwSwapBuffers(GLFWwindow* window);
GLFWAPI void glfwSwapInterval(int interval);

GLFWAPI int glfwExtensionSupported(const char* extension);

GLFWAPI GLFWglproc glfwGetProcAddress(const char* procname);

/*************************************************************************
 * Global definition cleanup
 *************************************************************************/

/* ------------------- BEGIN SYSTEM/COMPILER SPECIFIC -------------------- */

#ifdef GLFW_WINGDIAPI_DEFINED
 #undef WINGDIAPI
 #undef GLFW_WINGDIAPI_DEFINED
#endif

#ifdef GLFW_CALLBACK_DEFINED
 #undef CALLBACK
 #undef GLFW_CALLBACK_DEFINED
#endif

/* Some OpenGL related headers need GLAPIENTRY, but it is unconditionally
 * defined by some gl.h variants (OpenBSD) so define it after if needed.
 */
#ifndef GLAPIENTRY
 #define GLAPIENTRY APIENTRY
 #define GLFW_GLAPIENTRY_DEFINED
#endif

/* -------------------- END SYSTEM/COMPILER SPECIFIC --------------------- */

#ifdef __cplusplus
}
#endif