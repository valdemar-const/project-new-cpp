#pragma once

#include <cstdint>

namespace graphics
{

class Material
{
    struct Fill_Color
    {
        std::uint8_t r = 0x00;
        std::uint8_t g = 0x00;
        std::uint8_t b = 0x00;
        std::uint8_t a = 0xFF;
    } fill_color;
};

} // namespace graphics
