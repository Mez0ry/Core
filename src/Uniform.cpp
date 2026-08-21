#include "Uniform.hpp"
#include "Shader.hpp"
#include <glad/gl.h>
#include "glm/ext.hpp"
#include <spdlog/spdlog.h>

Uniform::Uniform(Shader & shader) : m_Shader(shader)
{
    if (!shader.IsValid()) {
        spdlog::error("Shader is invalid in Uniform constructor");
    }
}

void Uniform::SetUniformBlock(const Shader &shader, const std::string &block_name, int32_t uniform_block_idx)
{
    shader.UseShader();

    glUniformBlockBinding(shader.GetId(), Uniform::GetUniformBlockIndex(shader, block_name), uniform_block_idx);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        spdlog::error("OpenGL error when setting uniform block '{}': error: {}", block_name, error);
    }
}

void Uniform::SetUniformFloat1(const std::string &name, float v0)
{
    SetShaderUniformFloat1(m_Shader, name, v0);
}

void Uniform::SetUniformFloat2(const std::string &name, float v0, float v1)
{
    SetShaderUniformFloat2(m_Shader, name, v0, v1);
}

void Uniform::SetUniformFloat3(const std::string &name, float v0, float v1, float v2)
{
    SetShaderUniformFloat3(m_Shader, name, v0, v1, v2);
}

void Uniform::SetUniformFloat4(const std::string &name, float v0, float v1, float v2, float v3)
{
    SetShaderUniformFloat4(m_Shader, name, v0, v1, v2, v3);
}

void Uniform::SetUniformMat4(const std::string &name, const glm::mat<4, 4, glm::f32, glm::packed_highp>& mat, bool transpose)
{
    SetShaderUniformMat4(m_Shader, name, mat, transpose);
}

void Uniform::SetShaderUniformInt1(const Shader &shader, const std::string &name, int v0)
{
    if (!shader.IsValid()) {
        SPDLOG_WARN("Attempted to set uniform '{}' but shader is invalid.", name);
    }
    shader.UseShader();

    glUniform1i(Uniform::GetUniformLocation(shader, name), v0);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPDLOG_ERROR("OpenGL error when setting uniform '{}' in shader ID {}: {}", name, shader.GetId(), error);
    }
}

void Uniform::SetShaderUniformFloat1(const Shader &shader, const std::string &name, float v0)
{
    glUniform1f(Uniform::GetUniformLocation(shader, name), v0);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPDLOG_ERROR("OpenGL error when setting uniform '{}' in shader ID {}: {}", name, shader.GetId(), error);
    }
}

void Uniform::SetShaderUniformFloat2(const Shader &shader, const std::string &name, float v0, float v1)
{
    glUniform2f(Uniform::GetUniformLocation(shader, name), v0, v1);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPDLOG_ERROR("OpenGL error when setting uniform '{}' in shader ID {}: {}", name, shader.GetId(), error);
    }
}

void Uniform::SetShaderUniformFloat3(const Shader &shader, const std::string &name, float v0, float v1, float v2)
{
    glUniform3f(Uniform::GetUniformLocation(shader, name), v0, v1, v2);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPDLOG_ERROR("OpenGL error when setting uniform '{}' in shader ID {}: {}", name, shader.GetId(), error);
    }
}

void Uniform::SetShaderUniformFloat4(const Shader &shader, const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(Uniform::GetUniformLocation(shader, name), v0, v1, v2, v3);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPDLOG_ERROR("OpenGL error when setting uniform '{}' in shader ID {}: {}", name, shader.GetId(), error);
    }
}

void Uniform::SetShaderUniformMat4(const Shader &shader, const std::string &name, const glm::mat<4, 4, glm::f32, glm::packed_highp>& mat, bool transpose)
{
    glUniformMatrix4fv(Uniform::GetUniformLocation(shader, name), 1, transpose, glm::value_ptr(mat));
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPDLOG_ERROR("OpenGL error when setting uniform '{}' in shader ID {}: {}", name, shader.GetId(), error);
    }
}

int32_t Uniform::GetUniformLocation(const Shader &shader, const std::string &name)
{
    int32_t loc = glGetUniformLocation(shader.GetId(), name.c_str());
    if (loc == -1)
    {
        SPDLOG_WARN("Uniform '{}' not found in shader ID {}", name, shader.GetId());
    }
    return loc;
}

int32_t Uniform::GetUniformLocation(const std::string &name) const
{
    return Uniform::GetUniformLocation(m_Shader, name);
}

uint32_t Uniform::GetUniformBlockIndex(const std::string &name) const
{
    return Uniform::GetUniformBlockIndex(m_Shader, name);
}

uint32_t Uniform::GetUniformBlockIndex(const Shader &shader, const std::string &name)
{
    uint32_t block_index = glGetUniformBlockIndex(shader.GetId(), name.c_str());
    if (block_index == GL_INVALID_INDEX)
    {
        SPDLOG_WARN("Uniform block '{}' does not exist in shader ID {}", name, shader.GetId());
    }
    return block_index;
}