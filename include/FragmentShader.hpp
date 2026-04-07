#ifndef __FRAGMENT_SHADER_HPP__
#define __FRAGMENT_SHADER_HPP__
#include <string>
#include <optional>
#include <cstdint>

using GLint = int;

class FragmentShader
{
private:
    std::uint32_t m_Id;
    std::string m_ShaderSource;
public:
    explicit FragmentShader(const std::string& path, std::uint32_t count, const GLint* length = nullptr);
    explicit FragmentShader(const char* raw_shader, std::optional<size_t> length = std::nullopt);

    ~FragmentShader();

    /**
     * @param count: Specifies the number of elements in the string and length arrays.
     * @param length: Specifies an array of string lengths.
    */
    void Create(std::uint32_t count = 1, const GLint* length = nullptr);
    void Compile();

    std::uint32_t GetId() const;

    void DeleteShader();
private:
};
#endif //!__FRAGMENT_SHADER_HPP__