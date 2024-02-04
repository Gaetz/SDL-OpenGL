#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include "maths.h"

class Color
{
public:
    Color();
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    explicit Color(uint32_t i);

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    friend Color operator *(Color value, float scale)
    {
        return Color::multiply(value, scale);
    }	

    [[nodiscard]] Vector3 toVector3() const;
    [[nodiscard]] Vector4 toVector4() const;

    static Color lerp(Color value1, Color value2, float amount);
    static Color multiply(Color value, float scale);

    static Color black;
    static Color white;
    static Color red;
    static Color green;
    static Color blue;
    static Color yellow;
    static Color lightYellow;
    static Color lightBlue;
    static Color lightPink;
    static Color lightGreen;
};

#endif