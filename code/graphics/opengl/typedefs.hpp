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

using PFNGLCREATEBUFFERSPROC   = void(APIENTRY*)(int32_t n, uint32_t* buffers);
using PFNGLDELETEBUFFERSPROC   = void(APIENTRY*)(int32_t n, const uint32_t* buffers);
using PFNGLBINDBUFFERPROC      = void(APIENTRY*)(uint32_t target, uint32_t buffer);
using PFNGLNAMEDBUFFERDATAPROC = void(APIENTRY*)(uint32_t buffer, int64_t size, const void* data, uint32_t usage);

#pragma endregion