#ifndef __UNIFORM_HPP__
#define __UNIFORM_HPP__
#include <cstdint>
#include <optional>
#include <string>

class Shader;

class Uniform
{
private:
    Shader & m_Shader;
public:
    Uniform(Shader& shader);

    // Instance methods
    void SetUniformFloat1(const std::string &name, float v0);
    void SetUniformFloat2(const std::string &name, float v0, float v1);
    void SetUniformFloat3(const std::string &name, float v0, float v1, float v2);
    void SetUniformFloat4(const std::string &name, float v0, float v1, float v2, float v3);

    // Static methods for shader object
    static void SetShaderUniformInt1(const Shader &shader, const std::string &name, int v0);
    static void SetShaderUniformFloat1(const Shader &shader, const std::string &name, float v0);
    static void SetShaderUniformFloat2(const Shader &shader, const std::string &name, float v0, float v1);
    static void SetShaderUniformFloat3(const Shader &shader, const std::string &name, float v0, float v1, float v2);
    static void SetShaderUniformFloat4(const Shader &shader, const std::string &name, float v0, float v1, float v2, float v3);

    // Methods with explicit location
    static void SetUniformFloat1(int32_t location, float v0);
    static void SetUniformFloat2(int32_t location, float v0, float v1);
    static void SetUniformFloat3(int32_t location, float v0, float v1, float v2);
    static void SetUniformFloat4(int32_t location, float v0, float v1, float v2, float v3);

    int32_t GetUniformLocation(const std::string &name) const;
    static int GetUniformLocation(const Shader &shader, const std::string &name);
};
#endif //!__UNIFORM_HPP__