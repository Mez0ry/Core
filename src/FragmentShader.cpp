#include "FragmentShader.hpp"
#include <glad/gl.h>
#include "FileReader.hpp"

#include <spdlog/spdlog.h>

FragmentShader::FragmentShader(const std::string &path, std::uint32_t count, const GLint* length)
{
    constexpr auto shader_src_size = std::uint32_t(400);
    m_ShaderSource.reserve(shader_src_size);
    m_ShaderSource.assign(FileReader::ReadFile(path));
    Create(count, length);
    Compile();
}

FragmentShader::FragmentShader(const char *raw_shader, std::optional<size_t> length) : m_ShaderSource(raw_shader)
{
    m_ShaderSource.reserve(length.value_or(300));
    m_ShaderSource.assign(raw_shader);
    Create();
    Compile();
}

FragmentShader::~FragmentShader() {
    DeleteShader();
}

void FragmentShader::Create(std::uint32_t count, const GLint* length) {
    m_Id = glCreateShader(GL_FRAGMENT_SHADER);
    auto raw_shader = m_ShaderSource.c_str();
    glShaderSource(m_Id, count, &raw_shader, length);
}

void FragmentShader::Compile() {
    glCompileShader(m_Id);

    int  success;

    glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        const size_t size = 512;
        char info_log[size];
        glGetShaderInfoLog(m_Id, size, NULL, info_log);
        spdlog::error("Core::FragmentShader::Compile, status: COMPILATION_FAILED. log: {}", info_log);
    }
}

std::uint32_t FragmentShader::GetId() const
{
    return m_Id;
}

void FragmentShader::DeleteShader() {
    glDeleteShader(m_Id);
}
