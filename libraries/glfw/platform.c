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

#include <stdlib.h>

static const struct
{
    int ID;
    GLFWbool (*connect)(int,_GLFWplatform*);
} supportedPlatforms[] =
{
    { GLFW_PLATFORM_WIN32, _glfwConnectWin32 },
};

GLFWbool _glfwSelectPlatform(int desiredID, _GLFWplatform* platform)
{
    const size_t count = sizeof(supportedPlatforms) / sizeof(supportedPlatforms[0]);

    if (desiredID != GLFW_PLATFORM_WIN32)
    {
        _glfwInputError(GLFW_INVALID_ENUM, "Invalid platform ID 0x%08X", desiredID);
        return GLFW_FALSE;
    }

    if (count == 0)
    {
        _glfwInputError(GLFW_PLATFORM_UNAVAILABLE, "This binary only supports the Null platform");
        return GLFW_FALSE;
    }

    for (size_t i = 0;  i < count;  i++)
    {
        if (supportedPlatforms[i].ID == desiredID)
            return supportedPlatforms[i].connect(desiredID, platform);
    }

    _glfwInputError(GLFW_PLATFORM_UNAVAILABLE, "The requested platform is not supported");

    return GLFW_FALSE;
}