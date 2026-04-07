#ifndef __VERTEX_SHADER_HPP__
#define __VERTEX_SHADER_HPP__
#include <string>
#include <optional>
#include <cstdint>

using GLint = int;

class VertexShader
{
    std::uint32_t m_Id;
    std::string m_ShaderSource;
public:
    explicit VertexShader(const std::string& path, std::uint32_t count = 1, const GLint* length = 0);
    explicit VertexShader(const char* raw_shader, std::optional<size_t> length = std::nullopt);
    ~VertexShader();

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
#endif //!__VERTEX_SHADER_HPP__