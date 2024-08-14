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

/*! @brief Requests user attention to the specified window.
 *
 *  This function requests user attention to the specified window.  On
 *  platforms where this is not supported, attention is requested to the
 *  application as a whole.
 *
 *  Once the user has given attention, usually by focusing the window or
 *  application, the system will end the request automatically.
 *
 *  @param[in] window The window to request attention to.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @remark @macos Attention is requested to the application as a whole, not the
 *  specific window.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_attention
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup window
 */
GLFWAPI void glfwRequestWindowAttention(GLFWwindow* window);

/*! @brief Returns the monitor that the window uses for full screen mode.
 *
 *  This function returns the handle of the monitor that the specified window is
 *  in full screen on.
 *
 *  @param[in] window The window to query.
 *  @return The monitor, or `NULL` if the window is in windowed mode or an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_monitor
 *  @sa @ref glfwSetWindowMonitor
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI GLFWmonitor* glfwGetWindowMonitor(GLFWwindow* window);

/*! @brief Sets the mode, monitor, video mode and placement of a window.
 *
 *  This function sets the monitor that the window uses for full screen mode or,
 *  if the monitor is `NULL`, makes it windowed mode.
 *
 *  When setting a monitor, this function updates the width, height and refresh
 *  rate of the desired video mode and switches to the video mode closest to it.
 *  The window position is ignored when setting a monitor.
 *
 *  When the monitor is `NULL`, the position, width and height are used to
 *  place the window content area.  The refresh rate is ignored when no monitor
 *  is specified.
 *
 *  If you only wish to update the resolution of a full screen window or the
 *  size of a windowed mode window, see @ref glfwSetWindowSize.
 *
 *  When a window transitions from full screen to windowed mode, this function
 *  restores any previous window settings such as whether it is decorated,
 *  floating, resizable, has size or aspect ratio limits, etc.
 *
 *  @param[in] window The window whose monitor, size or video mode to set.
 *  @param[in] monitor The desired monitor, or `NULL` to set windowed mode.
 *  @param[in] xpos The desired x-coordinate of the upper-left corner of the
 *  content area.
 *  @param[in] ypos The desired y-coordinate of the upper-left corner of the
 *  content area.
 *  @param[in] width The desired with, in screen coordinates, of the content
 *  area or video mode.
 *  @param[in] height The desired height, in screen coordinates, of the content
 *  area or video mode.
 *  @param[in] refreshRate The desired refresh rate, in Hz, of the video mode,
 *  or `GLFW_DONT_CARE`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @remark The OpenGL or OpenGL ES context will not be destroyed or otherwise
 *  affected by any resizing or mode switching, although you may need to update
 *  your viewport if the framebuffer size has changed.
 *
 *  @remark @wayland The desired window position is ignored, as there is no way
 *  for an application to set this property.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_monitor
 *  @sa @ref window_full_screen
 *  @sa @ref glfwGetWindowMonitor
 *  @sa @ref glfwSetWindowSize
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup window
 */
GLFWAPI void glfwSetWindowMonitor(GLFWwindow* window, GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);

/*! @brief Returns an attribute of the specified window.
 *
 *  This function returns the value of an attribute of the specified window or
 *  its OpenGL or OpenGL ES context.
 *
 *  @param[in] window The window to query.
 *  @param[in] attrib The [window attribute](@ref window_attribs) whose value to
 *  return.
 *  @return The value of the attribute, or zero if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_ENUM and @ref GLFW_PLATFORM_ERROR.
 *
 *  @remark Framebuffer related hints are not window attributes.  See @ref
 *  window_attribs_fb for more information.
 *
 *  @remark Zero is a valid value for many window and context related
 *  attributes so you cannot use a return value of zero as an indication of
 *  errors.  However, this function should not fail as long as it is passed
 *  valid arguments and the library has been [initialized](@ref intro_init).
 *
 *  @remark @wayland The Wayland protocol provides no way to check whether a
 *  window is iconfied, so @ref GLFW_ICONIFIED always returns `GLFW_FALSE`.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_attribs
 *  @sa @ref glfwSetWindowAttrib
 *
 *  @since Added in version 3.0.  Replaces `glfwGetWindowParam` and
 *  `glfwGetGLVersion`.
 *
 *  @ingroup window
 */
GLFWAPI int glfwGetWindowAttrib(GLFWwindow* window, int attrib);

/*! @brief Sets an attribute of the specified window.
 *
 *  This function sets the value of an attribute of the specified window.
 *
 *  The supported attributes are [GLFW_DECORATED](@ref GLFW_DECORATED_attrib),
 *  [GLFW_RESIZABLE](@ref GLFW_RESIZABLE_attrib),
 *  [GLFW_FLOATING](@ref GLFW_FLOATING_attrib),
 *  [GLFW_AUTO_ICONIFY](@ref GLFW_AUTO_ICONIFY_attrib) and
 *  [GLFW_FOCUS_ON_SHOW](@ref GLFW_FOCUS_ON_SHOW_attrib).
 *  [GLFW_MOUSE_PASSTHROUGH](@ref GLFW_MOUSE_PASSTHROUGH_attrib)
 *
 *  Some of these attributes are ignored for full screen windows.  The new
 *  value will take effect if the window is later made windowed.
 *
 *  Some of these attributes are ignored for windowed mode windows.  The new
 *  value will take effect if the window is later made full screen.
 *
 *  @param[in] window The window to set the attribute for.
 *  @param[in] attrib A supported window attribute.
 *  @param[in] value `GLFW_TRUE` or `GLFW_FALSE`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_ENUM, @ref GLFW_INVALID_VALUE, @ref GLFW_PLATFORM_ERROR and @ref
 *  GLFW_FEATURE_UNAVAILABLE (see remarks).
 *
 *  @remark Calling @ref glfwGetWindowAttrib will always return the latest
 *  value, even if that value is ignored by the current mode of the window.
 *
 *  @remark @wayland The [GLFW_FLOATING](@ref GLFW_FLOATING_attrib) window attribute is
 *  not supported.  Setting this will emit @ref GLFW_FEATURE_UNAVAILABLE.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_attribs
 *  @sa @ref glfwGetWindowAttrib
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup window
 */
GLFWAPI void glfwSetWindowAttrib(GLFWwindow* window, int attrib, int value);

/*! @brief Sets the user pointer of the specified window.
 *
 *  This function sets the user-defined pointer of the specified window.  The
 *  current value is retained until the window is destroyed.  The initial value
 *  is `NULL`.
 *
 *  @param[in] window The window whose pointer to set.
 *  @param[in] pointer The new value.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @sa @ref window_userptr
 *  @sa @ref glfwGetWindowUserPointer
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI void glfwSetWindowUserPointer(GLFWwindow* window, void* pointer);

/*! @brief Returns the user pointer of the specified window.
 *
 *  This function returns the current value of the user-defined pointer of the
 *  specified window.  The initial value is `NULL`.
 *
 *  @param[in] window The window whose pointer to return.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @sa @ref window_userptr
 *  @sa @ref glfwSetWindowUserPointer
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI void* glfwGetWindowUserPointer(GLFWwindow* window);

/*! @brief Sets the position callback for the specified window.
 *
 *  This function sets the position callback of the specified window, which is
 *  called when the window is moved.  The callback is provided with the
 *  position, in screen coordinates, of the upper-left corner of the content
 *  area of the window.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int xpos, int ypos)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWwindowposfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @remark @wayland This callback will never be called, as there is no way for
 *  an application to know its global position.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_pos
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow* window, GLFWwindowposfun callback);

/*! @brief Sets the size callback for the specified window.
 *
 *  This function sets the size callback of the specified window, which is
 *  called when the window is resized.  The callback is provided with the size,
 *  in screen coordinates, of the content area of the window.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int width, int height)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWwindowsizefun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_size
 *
 *  @since Added in version 1.0.
 *  @glfw3 Added window handle parameter and return value.
 *
 *  @ingroup window
 */
GLFWAPI GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback);

/*! @brief Sets the close callback for the specified window.
 *
 *  This function sets the close callback of the specified window, which is
 *  called when the user attempts to close the window, for example by clicking
 *  the close widget in the title bar.
 *
 *  The close flag is set before this callback is called, but you can modify it
 *  at any time with @ref glfwSetWindowShouldClose.
 *
 *  The close callback is not triggered by @ref glfwDestroyWindow.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWwindowclosefun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @remark @macos Selecting Quit from the application menu will trigger the
 *  close callback for all windows.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_close
 *
 *  @since Added in version 2.5.
 *  @glfw3 Added window handle parameter and return value.
 *
 *  @ingroup window
 */
GLFWAPI GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindow* window, GLFWwindowclosefun callback);

/*! @brief Sets the refresh callback for the specified window.
 *
 *  This function sets the refresh callback of the specified window, which is
 *  called when the content area of the window needs to be redrawn, for example
 *  if the window has been exposed after having been covered by another window.
 *
 *  On compositing window systems such as Aero, Compiz, Aqua or Wayland, where
 *  the window contents are saved off-screen, this callback may be called only
 *  very infrequently or never at all.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window);
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWwindowrefreshfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_refresh
 *
 *  @since Added in version 2.5.
 *  @glfw3 Added window handle parameter and return value.
 *
 *  @ingroup window
 */
GLFWAPI GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow* window, GLFWwindowrefreshfun callback);

/*! @brief Sets the focus callback for the specified window.
 *
 *  This function sets the focus callback of the specified window, which is
 *  called when the window gains or loses input focus.
 *
 *  After the focus callback is called for a window that lost input focus,
 *  synthetic key and mouse button release events will be generated for all such
 *  that had been pressed.  For more information, see @ref glfwSetKeyCallback
 *  and @ref glfwSetMouseButtonCallback.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int focused)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWwindowfocusfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_focus
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindow* window, GLFWwindowfocusfun callback);

/*! @brief Sets the iconify callback for the specified window.
 *
 *  This function sets the iconification callback of the specified window, which
 *  is called when the window is iconified or restored.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int iconified)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWwindowiconifyfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_iconify
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindow* window, GLFWwindowiconifyfun callback);

/*! @brief Sets the maximize callback for the specified window.
 *
 *  This function sets the maximization callback of the specified window, which
 *  is called when the window is maximized or restored.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int maximized)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWwindowmaximizefun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_maximize
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup window
 */
GLFWAPI GLFWwindowmaximizefun glfwSetWindowMaximizeCallback(GLFWwindow* window, GLFWwindowmaximizefun callback);

/*! @brief Sets the framebuffer resize callback for the specified window.
 *
 *  This function sets the framebuffer resize callback of the specified window,
 *  which is called when the framebuffer of the specified window is resized.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int width, int height)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWframebuffersizefun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_fbsize
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup window
 */
GLFWAPI GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun callback);

/*! @brief Sets the window content scale callback for the specified window.
 *
 *  This function sets the window content scale callback of the specified window,
 *  which is called when the content scale of the specified window changes.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, float xscale, float yscale)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWwindowcontentscalefun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref window_scale
 *  @sa @ref glfwGetWindowContentScale
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup window
 */
GLFWAPI GLFWwindowcontentscalefun glfwSetWindowContentScaleCallback(GLFWwindow* window, GLFWwindowcontentscalefun callback);

/*! @brief Processes all pending events.
 *
 *  This function processes only those events that are already in the event
 *  queue and then returns immediately.  Processing events will cause the window
 *  and input callbacks associated with those events to be called.
 *
 *  On some platforms, a window move, resize or menu operation will cause event
 *  processing to block.  This is due to how event processing is designed on
 *  those platforms.  You can use the
 *  [window refresh callback](@ref window_refresh) to redraw the contents of
 *  your window when necessary during such operations.
 *
 *  Do not assume that callbacks you set will _only_ be called in response to
 *  event processing functions like this one.  While it is necessary to poll for
 *  events, window systems that require GLFW to register callbacks of its own
 *  can pass events to GLFW in response to many window system function calls.
 *  GLFW will pass those events on to the application callbacks before
 *  returning.
 *
 *  Event processing is not required for joystick input to work.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @reentrancy This function must not be called from a callback.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref events
 *  @sa @ref glfwWaitEvents
 *  @sa @ref glfwWaitEventsTimeout
 *
 *  @since Added in version 1.0.
 *
 *  @ingroup window
 */
GLFWAPI void glfwPollEvents(void);

/*! @brief Waits until events are queued and processes them.
 *
 *  This function puts the calling thread to sleep until at least one event is
 *  available in the event queue.  Once one or more events are available,
 *  it behaves exactly like @ref glfwPollEvents, i.e. the events in the queue
 *  are processed and the function then returns immediately.  Processing events
 *  will cause the window and input callbacks associated with those events to be
 *  called.
 *
 *  Since not all events are associated with callbacks, this function may return
 *  without a callback having been called even if you are monitoring all
 *  callbacks.
 *
 *  On some platforms, a window move, resize or menu operation will cause event
 *  processing to block.  This is due to how event processing is designed on
 *  those platforms.  You can use the
 *  [window refresh callback](@ref window_refresh) to redraw the contents of
 *  your window when necessary during such operations.
 *
 *  Do not assume that callbacks you set will _only_ be called in response to
 *  event processing functions like this one.  While it is necessary to poll for
 *  events, window systems that require GLFW to register callbacks of its own
 *  can pass events to GLFW in response to many window system function calls.
 *  GLFW will pass those events on to the application callbacks before
 *  returning.
 *
 *  Event processing is not required for joystick input to work.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @reentrancy This function must not be called from a callback.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref events
 *  @sa @ref glfwPollEvents
 *  @sa @ref glfwWaitEventsTimeout
 *
 *  @since Added in version 2.5.
 *
 *  @ingroup window
 */
GLFWAPI void glfwWaitEvents(void);

/*! @brief Waits with timeout until events are queued and processes them.
 *
 *  This function puts the calling thread to sleep until at least one event is
 *  available in the event queue, or until the specified timeout is reached.  If
 *  one or more events are available, it behaves exactly like @ref
 *  glfwPollEvents, i.e. the events in the queue are processed and the function
 *  then returns immediately.  Processing events will cause the window and input
 *  callbacks associated with those events to be called.
 *
 *  The timeout value must be a positive finite number.
 *
 *  Since not all events are associated with callbacks, this function may return
 *  without a callback having been called even if you are monitoring all
 *  callbacks.
 *
 *  On some platforms, a window move, resize or menu operation will cause event
 *  processing to block.  This is due to how event processing is designed on
 *  those platforms.  You can use the
 *  [window refresh callback](@ref window_refresh) to redraw the contents of
 *  your window when necessary during such operations.
 *
 *  Do not assume that callbacks you set will _only_ be called in response to
 *  event processing functions like this one.  While it is necessary to poll for
 *  events, window systems that require GLFW to register callbacks of its own
 *  can pass events to GLFW in response to many window system function calls.
 *  GLFW will pass those events on to the application callbacks before
 *  returning.
 *
 *  Event processing is not required for joystick input to work.
 *
 *  @param[in] timeout The maximum amount of time, in seconds, to wait.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_VALUE and @ref GLFW_PLATFORM_ERROR.
 *
 *  @reentrancy This function must not be called from a callback.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref events
 *  @sa @ref glfwPollEvents
 *  @sa @ref glfwWaitEvents
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup window
 */
GLFWAPI void glfwWaitEventsTimeout(double timeout);

/*! @brief Posts an empty event to the event queue.
 *
 *  This function posts an empty event from the current thread to the event
 *  queue, causing @ref glfwWaitEvents or @ref glfwWaitEventsTimeout to return.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref events
 *  @sa @ref glfwWaitEvents
 *  @sa @ref glfwWaitEventsTimeout
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup window
 */
GLFWAPI void glfwPostEmptyEvent(void);

/*! @brief Returns the value of an input option for the specified window.
 *
 *  This function returns the value of an input option for the specified window.
 *  The mode must be one of @ref GLFW_CURSOR, @ref GLFW_STICKY_KEYS,
 *  @ref GLFW_STICKY_MOUSE_BUTTONS, @ref GLFW_LOCK_KEY_MODS or
 *  @ref GLFW_RAW_MOUSE_MOTION.
 *
 *  @param[in] window The window to query.
 *  @param[in] mode One of `GLFW_CURSOR`, `GLFW_STICKY_KEYS`,
 *  `GLFW_STICKY_MOUSE_BUTTONS`, `GLFW_LOCK_KEY_MODS` or
 *  `GLFW_RAW_MOUSE_MOTION`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_INVALID_ENUM.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref glfwSetInputMode
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup input
 */
GLFWAPI int glfwGetInputMode(GLFWwindow* window, int mode);

/*! @brief Sets an input option for the specified window.
 *
 *  This function sets an input mode option for the specified window.  The mode
 *  must be one of @ref GLFW_CURSOR, @ref GLFW_STICKY_KEYS,
 *  @ref GLFW_STICKY_MOUSE_BUTTONS, @ref GLFW_LOCK_KEY_MODS
 *  @ref GLFW_RAW_MOUSE_MOTION, or @ref GLFW_UNLIMITED_MOUSE_BUTTONS.
 *
 *  If the mode is `GLFW_CURSOR`, the value must be one of the following cursor
 *  modes:
 *  - `GLFW_CURSOR_NORMAL` makes the cursor visible and behaving normally.
 *  - `GLFW_CURSOR_HIDDEN` makes the cursor invisible when it is over the
 *    content area of the window but does not restrict the cursor from leaving.
 *  - `GLFW_CURSOR_DISABLED` hides and grabs the cursor, providing virtual
 *    and unlimited cursor movement.  This is useful for implementing for
 *    example 3D camera controls.
 *  - `GLFW_CURSOR_CAPTURED` makes the cursor visible and confines it to the
 *    content area of the window.
 *
 *  If the mode is `GLFW_STICKY_KEYS`, the value must be either `GLFW_TRUE` to
 *  enable sticky keys, or `GLFW_FALSE` to disable it.  If sticky keys are
 *  enabled, a key press will ensure that @ref glfwGetKey returns `GLFW_PRESS`
 *  the next time it is called even if the key had been released before the
 *  call.  This is useful when you are only interested in whether keys have been
 *  pressed but not when or in which order.
 *
 *  If the mode is `GLFW_STICKY_MOUSE_BUTTONS`, the value must be either
 *  `GLFW_TRUE` to enable sticky mouse buttons, or `GLFW_FALSE` to disable it.
 *  If sticky mouse buttons are enabled, a mouse button press will ensure that
 *  @ref glfwGetMouseButton returns `GLFW_PRESS` the next time it is called even
 *  if the mouse button had been released before the call.  This is useful when
 *  you are only interested in whether mouse buttons have been pressed but not
 *  when or in which order.
 *
 *  If the mode is `GLFW_LOCK_KEY_MODS`, the value must be either `GLFW_TRUE` to
 *  enable lock key modifier bits, or `GLFW_FALSE` to disable them.  If enabled,
 *  callbacks that receive modifier bits will also have the @ref
 *  GLFW_MOD_CAPS_LOCK bit set when the event was generated with Caps Lock on,
 *  and the @ref GLFW_MOD_NUM_LOCK bit when Num Lock was on.
 *
 *  If the mode is `GLFW_RAW_MOUSE_MOTION`, the value must be either `GLFW_TRUE`
 *  to enable raw (unscaled and unaccelerated) mouse motion when the cursor is
 *  disabled, or `GLFW_FALSE` to disable it.  If raw motion is not supported,
 *  attempting to set this will emit @ref GLFW_FEATURE_UNAVAILABLE.  Call @ref
 *  glfwRawMouseMotionSupported to check for support.
 *
 *  If the mode is `GLFW_UNLIMITED_MOUSE_BUTTONS`, the value must be either
 *  `GLFW_TRUE` to disable the mouse button limit when calling the mouse button
 *  callback, or `GLFW_FALSE` to limit the mouse buttons sent to the callback
 *  to the mouse button token values up to `GLFW_MOUSE_BUTTON_LAST`.
 *
 *  @param[in] window The window whose input mode to set.
 *  @param[in] mode One of `GLFW_CURSOR`, `GLFW_STICKY_KEYS`,
 *  `GLFW_STICKY_MOUSE_BUTTONS`, `GLFW_LOCK_KEY_MODS` or
 *  `GLFW_RAW_MOUSE_MOTION`.
 *  @param[in] value The new value of the specified input mode.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_ENUM, @ref GLFW_PLATFORM_ERROR and @ref
 *  GLFW_FEATURE_UNAVAILABLE (see above).
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref glfwGetInputMode
 *
 *  @since Added in version 3.0.  Replaces `glfwEnable` and `glfwDisable`.
 *
 *  @ingroup input
 */
GLFWAPI void glfwSetInputMode(GLFWwindow* window, int mode, int value);

/*! @brief Returns whether raw mouse motion is supported.
 *
 *  This function returns whether raw mouse motion is supported on the current
 *  system.  This status does not change after GLFW has been initialized so you
 *  only need to check this once.  If you attempt to enable raw motion on
 *  a system that does not support it, @ref GLFW_PLATFORM_ERROR will be emitted.
 *
 *  Raw mouse motion is closer to the actual motion of the mouse across
 *  a surface.  It is not affected by the scaling and acceleration applied to
 *  the motion of the desktop cursor.  That processing is suitable for a cursor
 *  while raw motion is better for controlling for example a 3D camera.  Because
 *  of this, raw mouse motion is only provided when the cursor is disabled.
 *
 *  @return `GLFW_TRUE` if raw mouse motion is supported on the current machine,
 *  or `GLFW_FALSE` otherwise.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref raw_mouse_motion
 *  @sa @ref glfwSetInputMode
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup input
 */
GLFWAPI int glfwRawMouseMotionSupported(void);

/*! @brief Returns the layout-specific name of the specified printable key.
 *
 *  This function returns the name of the specified printable key, encoded as
 *  UTF-8.  This is typically the character that key would produce without any
 *  modifier keys, intended for displaying key bindings to the user.  For dead
 *  keys, it is typically the diacritic it would add to a character.
 *
 *  __Do not use this function__ for [text input](@ref input_char).  You will
 *  break text input for many languages even if it happens to work for yours.
 *
 *  If the key is `GLFW_KEY_UNKNOWN`, the scancode is used to identify the key,
 *  otherwise the scancode is ignored.  If you specify a non-printable key, or
 *  `GLFW_KEY_UNKNOWN` and a scancode that maps to a non-printable key, this
 *  function returns `NULL` but does not emit an error.
 *
 *  This behavior allows you to always pass in the arguments in the
 *  [key callback](@ref input_key) without modification.
 *
 *  The printable keys are:
 *  - `GLFW_KEY_APOSTROPHE`
 *  - `GLFW_KEY_COMMA`
 *  - `GLFW_KEY_MINUS`
 *  - `GLFW_KEY_PERIOD`
 *  - `GLFW_KEY_SLASH`
 *  - `GLFW_KEY_SEMICOLON`
 *  - `GLFW_KEY_EQUAL`
 *  - `GLFW_KEY_LEFT_BRACKET`
 *  - `GLFW_KEY_RIGHT_BRACKET`
 *  - `GLFW_KEY_BACKSLASH`
 *  - `GLFW_KEY_WORLD_1`
 *  - `GLFW_KEY_WORLD_2`
 *  - `GLFW_KEY_0` to `GLFW_KEY_9`
 *  - `GLFW_KEY_A` to `GLFW_KEY_Z`
 *  - `GLFW_KEY_KP_0` to `GLFW_KEY_KP_9`
 *  - `GLFW_KEY_KP_DECIMAL`
 *  - `GLFW_KEY_KP_DIVIDE`
 *  - `GLFW_KEY_KP_MULTIPLY`
 *  - `GLFW_KEY_KP_SUBTRACT`
 *  - `GLFW_KEY_KP_ADD`
 *  - `GLFW_KEY_KP_EQUAL`
 *
 *  Names for printable keys depend on keyboard layout, while names for
 *  non-printable keys are the same across layouts but depend on the application
 *  language and should be localized along with other user interface text.
 *
 *  @param[in] key The key to query, or `GLFW_KEY_UNKNOWN`.
 *  @param[in] scancode The scancode of the key to query.
 *  @return The UTF-8 encoded, layout-specific name of the key, or `NULL`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_VALUE, @ref GLFW_INVALID_ENUM and @ref GLFW_PLATFORM_ERROR.
 *
 *  @remark The contents of the returned string may change when a keyboard
 *  layout change event is received.
 *
 *  @pointer_lifetime The returned string is allocated and freed by GLFW.  You
 *  should not free it yourself.  It is valid until the library is terminated.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref input_key_name
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup input
 */
GLFWAPI const char* glfwGetKeyName(int key, int scancode);

/*! @brief Returns the platform-specific scancode of the specified key.
 *
 *  This function returns the platform-specific scancode of the specified key.
 *
 *  If the specified [key token](@ref keys) corresponds to a physical key not
 *  supported on the current platform then this method will return `-1`.
 *  Calling this function with anything other than a key token will return `-1`
 *  and generate a @ref GLFW_INVALID_ENUM error.
 *
 *  @param[in] key Any [key token](@ref keys).
 *  @return The platform-specific scancode for the key, or `-1` if the key is
 *  not supported on the current platform or an [error](@ref error_handling)
 *  occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_INVALID_ENUM.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref input_key
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup input
 */
GLFWAPI int glfwGetKeyScancode(int key);

/*! @brief Returns the last reported state of a keyboard key for the specified
 *  window.
 *
 *  This function returns the last state reported for the specified key to the
 *  specified window.  The returned state is one of `GLFW_PRESS` or
 *  `GLFW_RELEASE`.  The action `GLFW_REPEAT` is only reported to the key callback.
 *
 *  If the @ref GLFW_STICKY_KEYS input mode is enabled, this function returns
 *  `GLFW_PRESS` the first time you call it for a key that was pressed, even if
 *  that key has already been released.
 *
 *  The key functions deal with physical keys, with [key tokens](@ref keys)
 *  named after their use on the standard US keyboard layout.  If you want to
 *  input text, use the Unicode character callback instead.
 *
 *  The [modifier key bit masks](@ref mods) are not key tokens and cannot be
 *  used with this function.
 *
 *  __Do not use this function__ to implement [text input](@ref input_char).
 *
 *  @param[in] window The desired window.
 *  @param[in] key The desired [keyboard key](@ref keys).  `GLFW_KEY_UNKNOWN` is
 *  not a valid key for this function.
 *  @return One of `GLFW_PRESS` or `GLFW_RELEASE`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_INVALID_ENUM.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref input_key
 *
 *  @since Added in version 1.0.
 *  @glfw3 Added window handle parameter.
 *
 *  @ingroup input
 */
GLFWAPI int glfwGetKey(GLFWwindow* window, int key);

/*! @brief Returns the last reported state of a mouse button for the specified
 *  window.
 *
 *  This function returns the last state reported for the specified mouse button
 *  to the specified window.  The returned state is one of `GLFW_PRESS` or
 *  `GLFW_RELEASE`.
 *
 *  If the @ref GLFW_STICKY_MOUSE_BUTTONS input mode is enabled, this function
 *  returns `GLFW_PRESS` the first time you call it for a mouse button that was
 *  pressed, even if that mouse button has already been released.
 *
 *  The @ref GLFW_UNLIMITED_MOUSE_BUTTONS input mode does not effect the
 *  limit on buttons which can be polled with this function.
 *
 *  @param[in] window The desired window.
 *  @param[in] button The desired [mouse button token](@ref buttons).
 *  @return One of `GLFW_PRESS` or `GLFW_RELEASE`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_INVALID_ENUM.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref input_mouse_button
 *
 *  @since Added in version 1.0.
 *  @glfw3 Added window handle parameter.
 *
 *  @ingroup input
 */
GLFWAPI int glfwGetMouseButton(GLFWwindow* window, int button);

/*! @brief Retrieves the position of the cursor relative to the content area of
 *  the window.
 *
 *  This function returns the position of the cursor, in screen coordinates,
 *  relative to the upper-left corner of the content area of the specified
 *  window.
 *
 *  If the cursor is disabled (with `GLFW_CURSOR_DISABLED`) then the cursor
 *  position is unbounded and limited only by the minimum and maximum values of
 *  a `double`.
 *
 *  The coordinate can be converted to their integer equivalents with the
 *  `floor` function.  Casting directly to an integer type works for positive
 *  coordinates, but fails for negative ones.
 *
 *  Any or all of the position arguments may be `NULL`.  If an error occurs, all
 *  non-`NULL` position arguments will be set to zero.
 *
 *  @param[in] window The desired window.
 *  @param[out] xpos Where to store the cursor x-coordinate, relative to the
 *  left edge of the content area, or `NULL`.
 *  @param[out] ypos Where to store the cursor y-coordinate, relative to the to
 *  top edge of the content area, or `NULL`.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref cursor_pos
 *  @sa @ref glfwSetCursorPos
 *
 *  @since Added in version 3.0.  Replaces `glfwGetMousePos`.
 *
 *  @ingroup input
 */
GLFWAPI void glfwGetCursorPos(GLFWwindow* window, double* xpos, double* ypos);

/*! @brief Sets the position of the cursor, relative to the content area of the
 *  window.
 *
 *  This function sets the position, in screen coordinates, of the cursor
 *  relative to the upper-left corner of the content area of the specified
 *  window.  The window must have input focus.  If the window does not have
 *  input focus when this function is called, it fails silently.
 *
 *  __Do not use this function__ to implement things like camera controls.  GLFW
 *  already provides the `GLFW_CURSOR_DISABLED` cursor mode that hides the
 *  cursor, transparently re-centers it and provides unconstrained cursor
 *  motion.  See @ref glfwSetInputMode for more information.
 *
 *  If the cursor mode is `GLFW_CURSOR_DISABLED` then the cursor position is
 *  unconstrained and limited only by the minimum and maximum values of
 *  a `double`.
 *
 *  @param[in] window The desired window.
 *  @param[in] xpos The desired x-coordinate, relative to the left edge of the
 *  content area.
 *  @param[in] ypos The desired y-coordinate, relative to the top edge of the
 *  content area.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_PLATFORM_ERROR and @ref GLFW_FEATURE_UNAVAILABLE (see remarks).
 *
 *  @remark @wayland This function will only work when the cursor mode is
 *  `GLFW_CURSOR_DISABLED`, otherwise it will emit @ref GLFW_FEATURE_UNAVAILABLE.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref cursor_pos
 *  @sa @ref glfwGetCursorPos
 *
 *  @since Added in version 3.0.  Replaces `glfwSetMousePos`.
 *
 *  @ingroup input
 */
GLFWAPI void glfwSetCursorPos(GLFWwindow* window, double xpos, double ypos);

/*! @brief Creates a custom cursor.
 *
 *  Creates a new custom cursor image that can be set for a window with @ref
 *  glfwSetCursor.  The cursor can be destroyed with @ref glfwDestroyCursor.
 *  Any remaining cursors are destroyed by @ref glfwTerminate.
 *
 *  The pixels are 32-bit, little-endian, non-premultiplied RGBA, i.e. eight
 *  bits per channel with the red channel first.  They are arranged canonically
 *  as packed sequential rows, starting from the top-left corner.
 *
 *  The cursor hotspot is specified in pixels, relative to the upper-left corner
 *  of the cursor image.  Like all other coordinate systems in GLFW, the X-axis
 *  points to the right and the Y-axis points down.
 *
 *  @param[in] image The desired cursor image.
 *  @param[in] xhot The desired x-coordinate, in pixels, of the cursor hotspot.
 *  @param[in] yhot The desired y-coordinate, in pixels, of the cursor hotspot.
 *  @return The handle of the created cursor, or `NULL` if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_VALUE and @ref GLFW_PLATFORM_ERROR.
 *
 *  @pointer_lifetime The specified image data is copied before this function
 *  returns.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref cursor_object
 *  @sa @ref glfwDestroyCursor
 *  @sa @ref glfwCreateStandardCursor
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup input
 */
GLFWAPI GLFWcursor* glfwCreateCursor(const GLFWimage* image, int xhot, int yhot);

/*! @brief Creates a cursor with a standard shape.
 *
 *  Returns a cursor with a standard shape, that can be set for a window with
 *  @ref glfwSetCursor.  The images for these cursors come from the system
 *  cursor theme and their exact appearance will vary between platforms.
 *
 *  Most of these shapes are guaranteed to exist on every supported platform but
 *  a few may not be present.  See the table below for details.
 *
 *  Cursor shape                   | Windows | macOS | X11    | Wayland
 *  ------------------------------ | ------- | ----- | ------ | -------
 *  @ref GLFW_ARROW_CURSOR         | Yes     | Yes   | Yes    | Yes
 *  @ref GLFW_IBEAM_CURSOR         | Yes     | Yes   | Yes    | Yes
 *  @ref GLFW_CROSSHAIR_CURSOR     | Yes     | Yes   | Yes    | Yes
 *  @ref GLFW_POINTING_HAND_CURSOR | Yes     | Yes   | Yes    | Yes
 *  @ref GLFW_RESIZE_EW_CURSOR     | Yes     | Yes   | Yes    | Yes
 *  @ref GLFW_RESIZE_NS_CURSOR     | Yes     | Yes   | Yes    | Yes
 *  @ref GLFW_RESIZE_NWSE_CURSOR   | Yes     | Yes<sup>1</sup> | Maybe<sup>2</sup> | Maybe<sup>2</sup>
 *  @ref GLFW_RESIZE_NESW_CURSOR   | Yes     | Yes<sup>1</sup> | Maybe<sup>2</sup> | Maybe<sup>2</sup>
 *  @ref GLFW_RESIZE_ALL_CURSOR    | Yes     | Yes   | Yes    | Yes
 *  @ref GLFW_NOT_ALLOWED_CURSOR   | Yes     | Yes   | Maybe<sup>2</sup> | Maybe<sup>2</sup>
 *
 *  1) This uses a private system API and may fail in the future.
 *
 *  2) This uses a newer standard that not all cursor themes support.
 *
 *  If the requested shape is not available, this function emits a @ref
 *  GLFW_CURSOR_UNAVAILABLE error and returns `NULL`.
 *
 *  @param[in] shape One of the [standard shapes](@ref shapes).
 *  @return A new cursor ready to use or `NULL` if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_INVALID_ENUM, @ref GLFW_CURSOR_UNAVAILABLE and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref cursor_standard
 *  @sa @ref glfwCreateCursor
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup input
 */
GLFWAPI GLFWcursor* glfwCreateStandardCursor(int shape);

/*! @brief Destroys a cursor.
 *
 *  This function destroys a cursor previously created with @ref
 *  glfwCreateCursor.  Any remaining cursors will be destroyed by @ref
 *  glfwTerminate.
 *
 *  If the specified cursor is current for any window, that window will be
 *  reverted to the default cursor.  This does not affect the cursor mode.
 *
 *  @param[in] cursor The cursor object to destroy.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @reentrancy This function must not be called from a callback.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref cursor_object
 *  @sa @ref glfwCreateCursor
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup input
 */
GLFWAPI void glfwDestroyCursor(GLFWcursor* cursor);

/*! @brief Sets the cursor for the window.
 *
 *  This function sets the cursor image to be used when the cursor is over the
 *  content area of the specified window.  The set cursor will only be visible
 *  when the [cursor mode](@ref cursor_mode) of the window is
 *  `GLFW_CURSOR_NORMAL`.
 *
 *  On some platforms, the set cursor may not be visible unless the window also
 *  has input focus.
 *
 *  @param[in] window The window to set the cursor for.
 *  @param[in] cursor The cursor to set, or `NULL` to switch back to the default
 *  arrow cursor.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref cursor_object
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup input
 */
GLFWAPI void glfwSetCursor(GLFWwindow* window, GLFWcursor* cursor);

/*! @brief Sets the key callback.
 *
 *  This function sets the key callback of the specified window, which is called
 *  when a key is pressed, repeated or released.
 *
 *  The key functions deal with physical keys, with layout independent
 *  [key tokens](@ref keys) named after their values in the standard US keyboard
 *  layout.  If you want to input text, use the
 *  [character callback](@ref glfwSetCharCallback) instead.
 *
 *  When a window loses input focus, it will generate synthetic key release
 *  events for all pressed keys with associated key tokens.  You can tell these
 *  events from user-generated events by the fact that the synthetic ones are
 *  generated after the focus loss event has been processed, i.e. after the
 *  [window focus callback](@ref glfwSetWindowFocusCallback) has been called.
 *
 *  The scancode of a key is specific to that platform or sometimes even to that
 *  machine.  Scancodes are intended to allow users to bind keys that don't have
 *  a GLFW key token.  Such keys have `key` set to `GLFW_KEY_UNKNOWN`, their
 *  state is not saved and so it cannot be queried with @ref glfwGetKey.
 *
 *  Sometimes GLFW needs to generate synthetic key events, in which case the
 *  scancode may be zero.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new key callback, or `NULL` to remove the currently
 *  set callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int key, int scancode, int action, int mods)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWkeyfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref input_key
 *
 *  @since Added in version 1.0.
 *  @glfw3 Added window handle parameter and return value.
 *
 *  @ingroup input
 */
GLFWAPI GLFWkeyfun glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun callback);

/*! @brief Sets the Unicode character callback.
 *
 *  This function sets the character callback of the specified window, which is
 *  called when a Unicode character is input.
 *
 *  The character callback is intended for Unicode text input.  As it deals with
 *  characters, it is keyboard layout dependent, whereas the
 *  [key callback](@ref glfwSetKeyCallback) is not.  Characters do not map 1:1
 *  to physical keys, as a key may produce zero, one or more characters.  If you
 *  want to know whether a specific physical key was pressed or released, see
 *  the key callback instead.
 *
 *  The character callback behaves as system text input normally does and will
 *  not be called if modifier keys are held down that would prevent normal text
 *  input on that platform, for example a Super (Command) key on macOS or Alt key
 *  on Windows.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, unsigned int codepoint)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWcharfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref input_char
 *
 *  @since Added in version 2.4.
 *  @glfw3 Added window handle parameter and return value.
 *
 *  @ingroup input
 */
GLFWAPI GLFWcharfun glfwSetCharCallback(GLFWwindow* window, GLFWcharfun callback);

/*! @brief Sets the Unicode character with modifiers callback.
 *
 *  This function sets the character with modifiers callback of the specified
 *  window, which is called when a Unicode character is input regardless of what
 *  modifier keys are used.
 *
 *  The character with modifiers callback is intended for implementing custom
 *  Unicode character input.  For regular Unicode text input, see the
 *  [character callback](@ref glfwSetCharCallback).  Like the character
 *  callback, the character with modifiers callback deals with characters and is
 *  keyboard layout dependent.  Characters do not map 1:1 to physical keys, as
 *  a key may produce zero, one or more characters.  If you want to know whether
 *  a specific physical key was pressed or released, see the
 *  [key callback](@ref glfwSetKeyCallback) instead.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or an
 *  [error](@ref error_handling) occurred.
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, unsigned int codepoint, int mods)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWcharmodsfun).
 *
 *  @deprecated Scheduled for removal in version 4.0.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref input_char
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup input
 */
GLFWAPI GLFWcharmodsfun glfwSetCharModsCallback(GLFWwindow* window, GLFWcharmodsfun callback);

/*! @brief Sets the mouse button callback.
 *
 *  This function sets the mouse button callback of the specified window, which
 *  is called when a mouse button is pressed or released.
 *
 *  When a window loses input focus, it will generate synthetic mouse button
 *  release events for all pressed mouse buttons with associated button tokens.
 *  You can tell these events from user-generated events by the fact that the
 *  synthetic ones are generated after the focus loss event has been processed,
 *  i.e. after the [window focus callback](@ref glfwSetWindowFocusCallback) has
 *  been called.
 *
 *  The reported `button` value can be higher than `GLFW_MOUSE_BUTTON_LAST` if
 *  the button does not have an associated [button token](@ref buttons) and the
 *  @ref GLFW_UNLIMITED_MOUSE_BUTTONS input mode is set.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int button, int action, int mods)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWmousebuttonfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref input_mouse_button
 *
 *  @since Added in version 1.0.
 *  @glfw3 Added window handle parameter and return value.
 *
 *  @ingroup input
 */
GLFWAPI GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWwindow* window, GLFWmousebuttonfun callback);

/*! @brief Sets the cursor position callback.
 *
 *  This function sets the cursor position callback of the specified window,
 *  which is called when the cursor is moved.  The callback is provided with the
 *  position, in screen coordinates, relative to the upper-left corner of the
 *  content area of the window.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, double xpos, double ypos);
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWcursorposfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref cursor_pos
 *
 *  @since Added in version 3.0.  Replaces `glfwSetMousePosCallback`.
 *
 *  @ingroup input
 */
GLFWAPI GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);

/*! @brief Sets the cursor enter/leave callback.
 *
 *  This function sets the cursor boundary crossing callback of the specified
 *  window, which is called when the cursor enters or leaves the content area of
 *  the window.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new callback, or `NULL` to remove the currently set
 *  callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int entered)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWcursorenterfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref cursor_enter
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup input
 */
GLFWAPI GLFWcursorenterfun glfwSetCursorEnterCallback(GLFWwindow* window, GLFWcursorenterfun callback);

/*! @brief Sets the scroll callback.
 *
 *  This function sets the scroll callback of the specified window, which is
 *  called when a scrolling device is used, such as a mouse wheel or scrolling
 *  area of a touchpad.
 *
 *  The scroll callback receives all scrolling input, like that from a mouse
 *  wheel or a touchpad scrolling area.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new scroll callback, or `NULL` to remove the
 *  currently set callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, double xoffset, double yoffset)
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWscrollfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref scrolling
 *
 *  @since Added in version 3.0.  Replaces `glfwSetMouseWheelCallback`.
 *
 *  @ingroup input
 */
GLFWAPI GLFWscrollfun glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun callback);

/*! @brief Sets the path drop callback.
 *
 *  This function sets the path drop callback of the specified window, which is
 *  called when one or more dragged paths are dropped on the window.
 *
 *  Because the path array and its strings may have been generated specifically
 *  for that event, they are not guaranteed to be valid after the callback has
 *  returned.  If you wish to use them after the callback returns, you need to
 *  make a deep copy.
 *
 *  @param[in] window The window whose callback to set.
 *  @param[in] callback The new file drop callback, or `NULL` to remove the
 *  currently set callback.
 *  @return The previously set callback, or `NULL` if no callback was set or the
 *  library had not been [initialized](@ref intro_init).
 *
 *  @callback_signature
 *  @code
 *  void function_name(GLFWwindow* window, int path_count, const char* paths[])
 *  @endcode
 *  For more information about the callback parameters, see the
 *  [function pointer type](@ref GLFWdropfun).
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref path_drop
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup input
 */
GLFWAPI GLFWdropfun glfwSetDropCallback(GLFWwindow* window, GLFWdropfun callback);

/*! @brief Sets the clipboard to the specified string.
 *
 *  This function sets the system clipboard to the specified, UTF-8 encoded
 *  string.
 *
 *  @param[in] window Deprecated.  Any valid window or `NULL`.
 *  @param[in] string A UTF-8 encoded string.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @remark @win32 The clipboard on Windows has a single global lock for reading and
 *  writing.  GLFW tries to acquire it a few times, which is almost always enough.  If it
 *  cannot acquire the lock then this function emits @ref GLFW_PLATFORM_ERROR and returns.
 *  It is safe to try this multiple times.
 *
 *  @pointer_lifetime The specified string is copied before this function
 *  returns.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref clipboard
 *  @sa @ref glfwGetClipboardString
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup input
 */
GLFWAPI void glfwSetClipboardString(GLFWwindow* window, const char* string);

/*! @brief Returns the contents of the clipboard as a string.
 *
 *  This function returns the contents of the system clipboard, if it contains
 *  or is convertible to a UTF-8 encoded string.  If the clipboard is empty or
 *  if its contents cannot be converted, `NULL` is returned and a @ref
 *  GLFW_FORMAT_UNAVAILABLE error is generated.
 *
 *  @param[in] window Deprecated.  Any valid window or `NULL`.
 *  @return The contents of the clipboard as a UTF-8 encoded string, or `NULL`
 *  if an [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_FORMAT_UNAVAILABLE and @ref GLFW_PLATFORM_ERROR.
 *
 *  @remark @win32 The clipboard on Windows has a single global lock for reading and
 *  writing.  GLFW tries to acquire it a few times, which is almost always enough.  If it
 *  cannot acquire the lock then this function emits @ref GLFW_PLATFORM_ERROR and returns.
 *  It is safe to try this multiple times.
 *
 *  @pointer_lifetime The returned string is allocated and freed by GLFW.  You
 *  should not free it yourself.  It is valid until the next call to @ref
 *  glfwGetClipboardString or @ref glfwSetClipboardString, or until the library
 *  is terminated.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @sa @ref clipboard
 *  @sa @ref glfwSetClipboardString
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup input
 */
GLFWAPI const char* glfwGetClipboardString(GLFWwindow* window);

/*! @brief Returns the GLFW time.
 *
 *  This function returns the current GLFW time, in seconds.  Unless the time
 *  has been set using @ref glfwSetTime it measures time elapsed since GLFW was
 *  initialized.
 *
 *  This function and @ref glfwSetTime are helper functions on top of @ref
 *  glfwGetTimerFrequency and @ref glfwGetTimerValue.
 *
 *  The resolution of the timer is system dependent, but is usually on the order
 *  of a few micro- or nanoseconds.  It uses the highest-resolution monotonic
 *  time source on each operating system.
 *
 *  @return The current time, in seconds, or zero if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function may be called from any thread.  Reading and
 *  writing of the internal base time is not atomic, so it needs to be
 *  externally synchronized with calls to @ref glfwSetTime.
 *
 *  @sa @ref time
 *
 *  @since Added in version 1.0.
 *
 *  @ingroup input
 */
GLFWAPI double glfwGetTime(void);

/*! @brief Sets the GLFW time.
 *
 *  This function sets the current GLFW time, in seconds.  The value must be
 *  a positive finite number less than or equal to 18446744073.0, which is
 *  approximately 584.5 years.
 *
 *  This function and @ref glfwGetTime are helper functions on top of @ref
 *  glfwGetTimerFrequency and @ref glfwGetTimerValue.
 *
 *  @param[in] time The new value, in seconds.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref
 *  GLFW_INVALID_VALUE.
 *
 *  @remark The upper limit of GLFW time is calculated as
 *  floor((2<sup>64</sup> - 1) / 10<sup>9</sup>) and is due to implementations
 *  storing nanoseconds in 64 bits.  The limit may be increased in the future.
 *
 *  @thread_safety This function may be called from any thread.  Reading and
 *  writing of the internal base time is not atomic, so it needs to be
 *  externally synchronized with calls to @ref glfwGetTime.
 *
 *  @sa @ref time
 *
 *  @since Added in version 2.2.
 *
 *  @ingroup input
 */
GLFWAPI void glfwSetTime(double time);

/*! @brief Returns the current value of the raw timer.
 *
 *  This function returns the current value of the raw timer, measured in
 *  1&nbsp;/&nbsp;frequency seconds.  To get the frequency, call @ref
 *  glfwGetTimerFrequency.
 *
 *  @return The value of the timer, or zero if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref time
 *  @sa @ref glfwGetTimerFrequency
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup input
 */
GLFWAPI uint64_t glfwGetTimerValue(void);

/*! @brief Returns the frequency, in Hz, of the raw timer.
 *
 *  This function returns the frequency, in Hz, of the raw timer.
 *
 *  @return The frequency of the timer, in Hz, or zero if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref time
 *  @sa @ref glfwGetTimerValue
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup input
 */
GLFWAPI uint64_t glfwGetTimerFrequency(void);

/*! @brief Makes the context of the specified window current for the calling
 *  thread.
 *
 *  This function makes the OpenGL or OpenGL ES context of the specified window
 *  current on the calling thread.  It can also detach the current context from
 *  the calling thread without making a new one current by passing in `NULL`.
 *
 *  A context must only be made current on a single thread at a time and each
 *  thread can have only a single current context at a time.  Making a context
 *  current detaches any previously current context on the calling thread.
 *
 *  When moving a context between threads, you must detach it (make it
 *  non-current) on the old thread before making it current on the new one.
 *
 *  By default, making a context non-current implicitly forces a pipeline flush.
 *  On machines that support `GL_KHR_context_flush_control`, you can control
 *  whether a context performs this flush by setting the
 *  [GLFW_CONTEXT_RELEASE_BEHAVIOR](@ref GLFW_CONTEXT_RELEASE_BEHAVIOR_hint)
 *  hint.
 *
 *  The specified window must have an OpenGL or OpenGL ES context.  Specifying
 *  a window without a context will generate a @ref GLFW_NO_WINDOW_CONTEXT
 *  error.
 *
 *  @param[in] window The window whose context to make current, or `NULL` to
 *  detach the current context.
 *
 *  @remarks If the previously current context was created via a different
 *  context creation API than the one passed to this function, GLFW will still
 *  detach the previous one from its API before making the new one current.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_NO_WINDOW_CONTEXT and @ref GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref context_current
 *  @sa @ref glfwGetCurrentContext
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup context
 */
GLFWAPI void glfwMakeContextCurrent(GLFWwindow* window);

/*! @brief Returns the window whose context is current on the calling thread.
 *
 *  This function returns the window whose OpenGL or OpenGL ES context is
 *  current on the calling thread.
 *
 *  @return The window whose context is current, or `NULL` if no window's
 *  context is current.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref context_current
 *  @sa @ref glfwMakeContextCurrent
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup context
 */
GLFWAPI GLFWwindow* glfwGetCurrentContext(void);

/*! @brief Swaps the front and back buffers of the specified window.
 *
 *  This function swaps the front and back buffers of the specified window when
 *  rendering with OpenGL or OpenGL ES.  If the swap interval is greater than
 *  zero, the GPU driver waits the specified number of screen updates before
 *  swapping the buffers.
 *
 *  The specified window must have an OpenGL or OpenGL ES context.  Specifying
 *  a window without a context will generate a @ref GLFW_NO_WINDOW_CONTEXT
 *  error.
 *
 *  This function does not apply to Vulkan.  If you are rendering with Vulkan,
 *  see `vkQueuePresentKHR` instead.
 *
 *  @param[in] window The window whose buffers to swap.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_NO_WINDOW_CONTEXT and @ref GLFW_PLATFORM_ERROR.
 *
 *  @remark __EGL:__ The context of the specified window must be current on the
 *  calling thread.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref buffer_swap
 *  @sa @ref glfwSwapInterval
 *
 *  @since Added in version 1.0.
 *  @glfw3 Added window handle parameter.
 *
 *  @ingroup window
 */
GLFWAPI void glfwSwapBuffers(GLFWwindow* window);

/*! @brief Sets the swap interval for the current context.
 *
 *  This function sets the swap interval for the current OpenGL or OpenGL ES
 *  context, i.e. the number of screen updates to wait from the time @ref
 *  glfwSwapBuffers was called before swapping the buffers and returning.  This
 *  is sometimes called _vertical synchronization_, _vertical retrace
 *  synchronization_ or just _vsync_.
 *
 *  A context that supports either of the `WGL_EXT_swap_control_tear` and
 *  `GLX_EXT_swap_control_tear` extensions also accepts _negative_ swap
 *  intervals, which allows the driver to swap immediately even if a frame
 *  arrives a little bit late.  You can check for these extensions with @ref
 *  glfwExtensionSupported.
 *
 *  A context must be current on the calling thread.  Calling this function
 *  without a current context will cause a @ref GLFW_NO_CURRENT_CONTEXT error.
 *
 *  This function does not apply to Vulkan.  If you are rendering with Vulkan,
 *  see the present mode of your swapchain instead.
 *
 *  @param[in] interval The minimum number of screen updates to wait for
 *  until the buffers are swapped by @ref glfwSwapBuffers.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_NO_CURRENT_CONTEXT and @ref GLFW_PLATFORM_ERROR.
 *
 *  @remark This function is not called during context creation, leaving the
 *  swap interval set to whatever is the default for that API.  This is done
 *  because some swap interval extensions used by GLFW do not allow the swap
 *  interval to be reset to zero once it has been set to a non-zero value.
 *
 *  @remark Some GPU drivers do not honor the requested swap interval, either
 *  because of a user setting that overrides the application's request or due to
 *  bugs in the driver.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref buffer_swap
 *  @sa @ref glfwSwapBuffers
 *
 *  @since Added in version 1.0.
 *
 *  @ingroup context
 */
GLFWAPI void glfwSwapInterval(int interval);

/*! @brief Returns whether the specified extension is available.
 *
 *  This function returns whether the specified
 *  [API extension](@ref context_glext) is supported by the current OpenGL or
 *  OpenGL ES context.  It searches both for client API extension and context
 *  creation API extensions.
 *
 *  A context must be current on the calling thread.  Calling this function
 *  without a current context will cause a @ref GLFW_NO_CURRENT_CONTEXT error.
 *
 *  As this functions retrieves and searches one or more extension strings each
 *  call, it is recommended that you cache its results if it is going to be used
 *  frequently.  The extension strings will not change during the lifetime of
 *  a context, so there is no danger in doing this.
 *
 *  This function does not apply to Vulkan.  If you are using Vulkan, see @ref
 *  glfwGetRequiredInstanceExtensions, `vkEnumerateInstanceExtensionProperties`
 *  and `vkEnumerateDeviceExtensionProperties` instead.
 *
 *  @param[in] extension The ASCII encoded name of the extension.
 *  @return `GLFW_TRUE` if the extension is available, or `GLFW_FALSE`
 *  otherwise.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_NO_CURRENT_CONTEXT, @ref GLFW_INVALID_VALUE and @ref
 *  GLFW_PLATFORM_ERROR.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref context_glext
 *  @sa @ref glfwGetProcAddress
 *
 *  @since Added in version 1.0.
 *
 *  @ingroup context
 */
GLFWAPI int glfwExtensionSupported(const char* extension);

/*! @brief Returns the address of the specified function for the current
 *  context.
 *
 *  This function returns the address of the specified OpenGL or OpenGL ES
 *  [core or extension function](@ref context_glext), if it is supported
 *  by the current context.
 *
 *  A context must be current on the calling thread.  Calling this function
 *  without a current context will cause a @ref GLFW_NO_CURRENT_CONTEXT error.
 *
 *  This function does not apply to Vulkan.  If you are rendering with Vulkan,
 *  see @ref glfwGetInstanceProcAddress, `vkGetInstanceProcAddr` and
 *  `vkGetDeviceProcAddr` instead.
 *
 *  @param[in] procname The ASCII encoded name of the function.
 *  @return The address of the function, or `NULL` if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref GLFW_NOT_INITIALIZED, @ref
 *  GLFW_NO_CURRENT_CONTEXT and @ref GLFW_PLATFORM_ERROR.
 *
 *  @remark The address of a given function is not guaranteed to be the same
 *  between contexts.
 *
 *  @remark This function may return a non-`NULL` address despite the
 *  associated version or extension not being available.  Always check the
 *  context version or extension string first.
 *
 *  @pointer_lifetime The returned function pointer is valid until the context
 *  is destroyed or the library is terminated.
 *
 *  @thread_safety This function may be called from any thread.
 *
 *  @sa @ref context_glext
 *  @sa @ref glfwExtensionSupported
 *
 *  @since Added in version 1.0.
 *
 *  @ingroup context
 */
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