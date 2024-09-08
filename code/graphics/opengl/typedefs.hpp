#pragma once

#ifndef APIENTRY
#define APIENTRY
#endif

#pragma region core

using PFNGLCLEARPROC        = void(APIENTRY*)(uint32_t mask);
using PFNGLCLEARCOLORPROC   = void(APIENTRY*)(float red, float green, float blue, float alpha);
using PFNGLDRAWARRAYSPROC   = void(APIENTRY*)(uint32_t mode, int32_t first, int32_t count);
using PFNGLDRAWELEMENTSPROC = void(APIENTRY*)(uint32_t mode, int32_t count, uint32_t type, const void* indices);

#pragma endregion
#pragma region extended

using PFNGLBINDVERTEXARRAYPROC          = void(APIENTRY*)(uint32_t array);
using PFNGLCREATEVERTEXARRAYSPROC       = void(APIENTRY*)(int32_t n, uint32_t* arrays);
using PFNGLDELETEVERTEXARRAYSPROC       = void(APIENTRY*)(int32_t n, const uint32_t* arrays);
using PFNGLENABLEVERTEXARRAYATTRIBPROC  = void(APIENTRY*)(uint32_t vaobj, uint32_t index);
using PFNGLVERTEXARRAYATTRIBFORMATPROC  = void(APIENTRY*)(uint32_t vaobj, uint32_t attribindex,  int32_t size, uint32_t type, uint8_t normalized, uint32_t relativeoffset);
using PFNGLVERTEXARRAYATTRIBBINDINGPROC = void(APIENTRY*)(uint32_t vaobj, uint32_t attribindex,  uint32_t bindingindex);
using PFNGLVERTEXARRAYVERTEXBUFFERPROC  = void(APIENTRY*)(uint32_t vaobj, uint32_t bindingindex, uint32_t buffer, int64_t offset, int32_t stride);
using PFNGLVERTEXARRAYELEMENTBUFFERPROC = void(APIENTRY*)(uint32_t vaobj, uint32_t buffer);

using PFNGLCREATEBUFFERSPROC      = void(APIENTRY*)(int32_t n, uint32_t* buffers);
using PFNGLDELETEBUFFERSPROC      = void(APIENTRY*)(int32_t n, const uint32_t* buffers);
using PFNGLNAMEDBUFFERDATAPROC    = void(APIENTRY*)(uint32_t buffer, int64_t size, const void* data, uint32_t usage);
using PFNGLBINDBUFFERBASEPROC     = void(APIENTRY*)(uint32_t target, uint32_t index, uint32_t buffer);
using PFNGLNAMEDBUFFERSUBDATAPROC = void(APIENTRY*)(uint32_t buffer, int64_t offset, int64_t size, const void* data);

using PFNGLCREATESHADERPROC = uint32_t(APIENTRY*)(uint32_t type);
using PFNGLDELETESHADERPROC =     void(APIENTRY*)(uint32_t shader);
using PFNGLSHADERBINARYPROC =     void(APIENTRY*)(int32_t count, const uint32_t* shaders, uint32_t binary_format, const void* binary, int32_t length);
using PFNGLSPECIALIZESHADERPROC = void(APIENTRY*)(uint32_t shader, const char* entry_point, uint32_t constants, const uint32_t* constant_index, const uint32_t* constant_value);

using PFNGLCREATEPROGRAMPROC = uint32_t(APIENTRY*)();
using PFNGLATTACHSHADERPROC  =     void(APIENTRY*)(uint32_t program, uint32_t shader);
using PFNGLLINKPROGRAMPROC   =     void(APIENTRY*)(uint32_t program);
using PFNGLUSEPROGRAMPROC              = void(APIENTRY*)(uint32_t program);
using PFNGLDELETEPROGRAMPROC           = void(APIENTRY*)(uint32_t program);
using PFNGLPROGRAMUNIFORMMATRIX4FVPROC = void(APIENTRY*)(uint32_t program, int32_t location, int32_t count, uint8_t transpose, const float* value);

#pragma endregion