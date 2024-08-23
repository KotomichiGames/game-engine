#pragma once

namespace engine::win32
{
    constexpr uint32_t draw_to_window_arb   = 0x2001;
    constexpr uint32_t support_opengl_arb   = 0x2010;
    constexpr uint32_t double_buffer_arb    = 0x2011;
    constexpr uint32_t pixel_type_arb       = 0x2013;
    constexpr uint32_t type_rgba_arb        = 0x202b;
    constexpr uint32_t color_bits_arb       = 0x2014;
    constexpr uint32_t depth_bits_arb       = 0x2022;
    constexpr uint32_t stencil_bits_arb     = 0x2023;
    constexpr uint32_t samples_arb          = 0x2042;
    constexpr uint32_t framebuffer_srgb_arb = 0x20a9;

    constexpr uint32_t context_major_version_arb    = 0x2091;
    constexpr uint32_t context_minor_version_arb    = 0x2092;
    constexpr uint32_t context_profile_mask_arb     = 0x9126;
    constexpr uint32_t context_core_profile_bit_arb = 0x00000001;
}