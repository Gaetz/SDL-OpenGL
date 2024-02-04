#include "color.h"

Color::Color() : r(255), g(255), b(255), a(255) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
: r(r), g(g), b(b), a(a) {}

Color::Color(uint32_t i)
{
    r = static_cast<uint8_t>(i & 0x000000FF);
    g = static_cast<uint8_t>((i & 0x0000FF00) >> 8);
    b = static_cast<uint8_t>((i & 0x00FF0000) >> 16);
    a = static_cast<uint8_t>((i & 0xFF000000) >> 24);
}

Color Color::lerp(Color value1, Color value2, float amount)
{
    auto r = static_cast<uint8_t>(Math::lerp(value1.r, value2.r, amount));
    auto g = static_cast<uint8_t>(value1.g, value2.g, amount);
    auto b = static_cast<uint8_t>(value1.b, value2.b, amount);
    auto a = static_cast<uint8_t>(value1.a, value2.a, amount);
    
    return {r, g, b, a};
}
		
Color Color::multiply(Color value, float scale)
{
    auto r = static_cast<uint8_t>(static_cast<float>(value.r) * scale);
    auto g = static_cast<uint8_t>(static_cast<float>(value.g) * scale);
    auto b = static_cast<uint8_t>(static_cast<float>(value.b) * scale);
    auto a = static_cast<uint8_t>(static_cast<float>(value.a) * scale);
    
    return {r, g, b, a};
}	

Vector3 Color::toVector3() const
{
    Vector3 vector = Vector3(static_cast<float>(r)/255.0f, static_cast<float>(g)/255.0f, static_cast<float>(b)/255.0f);
    return vector;
}

Vector4 Color::toVector4() const
{
    Vector4 vector = Vector4(r, g, b, a);
    return vector;
}

Color Color::black {0, 0, 0};
Color Color::white {255, 255, 255};
Color Color::red {255, 0, 0};
Color Color::green {0, 255, 0};
Color Color::blue {0, 0, 255};
Color Color::yellow {255, 255, 0};
Color Color::lightYellow {255, 255, 225};
Color Color::lightBlue {170, 217, 230};
Color Color::lightPink {255, 180, 200};
Color Color::lightGreen {142, 240, 142};
