#include "Color.hpp"
#include "Color.hpp"
#include "MinMax.hpp"
#include <stdexcept>
#include <string>

Color::Color(float r, float g, float b, float a)
{
    m_Red = Bound(0.f, r, 1.0f);
    m_Green = Bound(0.f, g, 1.0f);
    m_Blue = Bound(0.f, b, 1.0f);
    m_Alpha = Bound(0.f, a, 1.0f);
}

Color::Color(int32_t r, int32_t g, int32_t b, int32_t a)
{
    m_Red = Bound(0.f, r / 255.0f, 1.0f);
    m_Green = Bound(0.f, g / 255.0f, 1.0f);
    m_Blue = Bound(0.f, b / 255.0f, 1.0f);
    m_Alpha = Bound(0.f, a / 255.0f, 1.0f);
}

Color::Color(const glm::vec4 &color)
{
    m_Red = Bound(0.f, color.x / 255.0f, 1.0f);
    m_Green = Bound(0.f, color.y / 255.0f, 1.0f);
    m_Blue = Bound(0.f, color.z / 255.0f, 1.0f);
    m_Alpha = Bound(0.f, color.w / 255.0f, 1.0f);
}

Color::Color(const char *name)
{
    std::string str(name);

    if (!str.empty() && str[0] == '#') {
        str.erase(0, 1);
    }

    size_t len = str.length();

    std::uint32_t r_int = 0, g_int = 0, b_int = 0, a_int = 255;

    try {
        if (len == 6 || len == 8) {
            const int base = 16;
            r_int = std::stoi(str.substr(0, 2), nullptr, base);
            g_int = std::stoi(str.substr(2, 2), nullptr, base);
            b_int = std::stoi(str.substr(4, 2), nullptr, base);

            if (len == 8) {
                a_int = std::stoi(str.substr(6, 2), nullptr, base);
            }
        } else {
            r_int = g_int = b_int = 0;
            a_int = 255;
        }
    } catch (const std::invalid_argument& e) {
        r_int = g_int = b_int = 0;
        a_int = 255;
    }
    
    m_Red = Normalize(r_int);
    m_Green = Normalize(g_int);
    m_Blue = Normalize(b_int);
    m_Alpha = Normalize(a_int);
}

float Color::RedF() const { return m_Red; }
float Color::GreenF() const { return m_Green; }
float Color::BlueF() const { return m_Blue; }
float Color::AlphaF() const { return m_Alpha; }

int32_t Color::Red() const { return static_cast<int32_t>(m_Red * 255.0f); }
int32_t Color::Green() const { return static_cast<int32_t>(m_Green * 255.0f); }
int32_t Color::Blue() const { return static_cast<int32_t>(m_Blue * 255.0f); }
int32_t Color::Alpha() const { return static_cast<int32_t>(m_Alpha * 255.0f); }
