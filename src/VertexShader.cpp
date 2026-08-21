#include "VertexShader.hpp"
#include <glad/gl.h>

#include "FileReader.hpp"
#include <spdlog/spdlog.h>

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

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        spdlog::error("VertexShader::Create Error setting shader source: {}", error);
        throw std::runtime_error("Error setting shader source");
    }
}

void VertexShader::Compile() {
    glCompileShader(m_Id);
    
    int  success;
    glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        const size_t log_size = 512;
        char info_log[log_size];
        glGetShaderInfoLog(m_Id, 512, NULL, info_log);
        spdlog::error("VertexShader::Compile, status: COMPILATION_FAILED, info log: {}", info_log);
        throw std::runtime_error(std::string("VertexShader compilation failed: ") + info_log);
    }else {
        #ifdef CORE_DEBUG
            SPDLOG_INFO("VertexShader compiled successfully");
        #endif
    }
}

std::uint32_t VertexShader::GetId() const
{
    return m_Id;
}

void VertexShader::DeleteShader() {
    if(m_Id == 0){
        spdlog::warn("Attempted to delete an invalid shader ID");
        return;
    }

    glDeleteShader(m_Id);
    m_Id = 0;
}
