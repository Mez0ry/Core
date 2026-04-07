#include "VertexShader.hpp"
#include <glad/gl.h>

#include "FileReader.hpp"
#include <iostream>

VertexShader::VertexShader(const std::string &path, std::uint32_t count, const GLint* length) 
{
    constexpr auto shader_src_size = std::uint32_t(300);
    m_ShaderSource.reserve(shader_src_size);
    m_ShaderSource.assign(FileReader::ReadFile(path));
    Create(count, length);
    Compile();
}

VertexShader::VertexShader(const char *raw_shader, std::optional<size_t> length) : m_ShaderSource(raw_shader)
{
    m_ShaderSource.reserve(length.value_or(300));
    m_ShaderSource.assign(raw_shader);
    Create();
    Compile();
}

VertexShader::~VertexShader() {
    DeleteShader();
}

void VertexShader::Create(std::uint32_t count, const GLint* length) {
    m_Id = glCreateShader(GL_VERTEX_SHADER);
    auto raw_shader = m_ShaderSource.c_str();
    glShaderSource(m_Id, count, &raw_shader, length);
}

void VertexShader::Compile() {
    glCompileShader(m_Id);
    
    int  success;
    char info_log[512];
    glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(m_Id, 512, NULL, info_log);
        std::cout << "VertexShader::Compile, status: COMPILATION_FAILED, info log: " << info_log << '\n';
    }
}

std::uint32_t VertexShader::GetId() const
{
    return m_Id;
}

void VertexShader::DeleteShader() {
    glDeleteShader(m_Id);
}
