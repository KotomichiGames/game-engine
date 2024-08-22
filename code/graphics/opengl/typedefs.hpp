#pragma once

#pragma region defines

#ifndef APIENTRY // TODO see if we can remove this at some point
#define APIENTRY
#endif

#pragma endregion
#pragma region core

using PFNGLCLEARCOLORPROC   = void(APIENTRY*)(float red, float green, float blue, float alpha);
using PFNGLCLEARPROC        = void(APIENTRY*)(uint32_t mask);
using PFNGLDRAWARRAYSPROC   = void(APIENTRY*)(uint32_t mode, int32_t first, int32_t count);
using PFNGLDRAWELEMENTSPROC = void(APIENTRY*)(uint32_t mode, int32_t count, uint32_t type, const void* indices);

#pragma endregion
#pragma region extended

using PFNGLCREATEVERTEXARRAYSPROC = void(APIENTRY*)(int32_t n, uint32_t* arrays);
using PFNGLBINDVERTEXARRAYPROC    = void(APIENTRY*)(uint32_t array);
using PFNGLDELETEVERTEXARRAYSPROC = void(APIENTRY*)(int32_t n, const uint32_t* arrays);

#pragma endregion