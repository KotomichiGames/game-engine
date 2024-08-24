#pragma once

#pragma region core

using PFNGLCLEARPROC        = void(APIENTRY*)(uint32_t mask);
using PFNGLCLEARCOLORPROC   = void(APIENTRY*)(float red, float green, float blue, float alpha);
using PFNGLDRAWARRAYSPROC   = void(APIENTRY*)(uint32_t mode, int32_t first, int32_t count);
using PFNGLDRAWELEMENTSPROC = void(APIENTRY*)(uint32_t mode, int32_t count, uint32_t type, const void* indices);

#pragma endregion
#pragma region extended

using PFNGLCREATEVERTEXARRAYSPROC = void(APIENTRY*)(int32_t n, uint32_t* arrays);
using PFNGLBINDVERTEXARRAYPROC    = void(APIENTRY*)(uint32_t array);
using PFNGLDELETEVERTEXARRAYSPROC = void(APIENTRY*)(int32_t n, const uint32_t* arrays);

#pragma endregion