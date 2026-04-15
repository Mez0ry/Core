#ifndef __COLOR_HPP__
#define __COLOR_HPP__
#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

class Color{
private:
    float m_Red, m_Green, m_Blue, m_Alpha;
public:
    explicit Color(float r, float g, float b, float a);
    explicit Color(int32_t r, int32_t g, int32_t b, int32_t a);
    explicit Color(const glm::vec4& color);
    Color(const char* name);
    
    float RedF() const;
    float GreenF() const;
    float BlueF() const;
    float AlphaF() const;
    //
    int32_t Red() const;
    int32_t Green() const;
    int32_t Blue() const;
    int32_t Alpha() const;

    template <typename TValue, typename TRet = float>
    inline TRet Normalize(const TValue& value, const float divisor = 255.0f) const{
        return static_cast<TRet>(value / divisor);
    }
private:
};
#endif //!__COLOR_HPP__