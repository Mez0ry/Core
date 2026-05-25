#include "Uniform.hpp"
#include "Shader.hpp"
#include <glad/gl.h>
#include "glm/ext.hpp"

Uniform::Uniform(Shader & shader) : m_Shader(shader)
{
    
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
    glUniform1i(Uniform::GetUniformLocation(shader,name), v0);
}

void Uniform::SetShaderUniformFloat1(const Shader &shader, const std::string &name, float v0)
{
    glUniform1f(Uniform::GetUniformLocation(shader,name), v0);
}

void Uniform::SetShaderUniformFloat2(const Shader &shader, const std::string &name, float v0, float v1)
{
    glUniform2f(Uniform::GetUniformLocation(shader, name), v0, v1);
}

void Uniform::SetShaderUniformFloat3(const Shader &shader, const std::string &name, float v0, float v1, float v2)
{
    glUniform3f(Uniform::GetUniformLocation(shader,name), v0, v1, v2);
}

void Uniform::SetShaderUniformFloat4(const Shader &shader, const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(Uniform::GetUniformLocation(shader,name), v0, v1 , v2, v3);
}

void Uniform::SetShaderUniformMat4(const Shader &shader, const std::string &name, const glm::mat<4, 4, glm::f32, glm::packed_highp>& mat, bool transpose)
{
    glUniformMatrix4fv(Uniform::GetUniformLocation(shader,name), 1, transpose, glm::value_ptr(mat));
}

void Uniform::SetUniformFloat1(int32_t location, float v0) {
    glUniform1f(location, v0);
}

void Uniform::SetUniformFloat2(int32_t location, float v0, float v1){
    glUniform2f(location, v0, v1);
}

void Uniform::SetUniformFloat3(int32_t location, float v0, float v1, float v2) {
    glUniform3f(location, v0, v1, v2);
}

void Uniform::SetUniformFloat4(int32_t location, float v0, float v1, float v2, float v3){
    glUniform4f(location, v0, v1, v2, v3);
}

void Uniform::SetUniformMat4(int32_t location, const glm::mat<4, 4, glm::f32, glm::packed_highp> &mat, bool transpose)
{
    glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(mat));
}

int32_t Uniform::GetUniformLocation(const Shader &shader, const std::string &name)
{
    int32_t loc = glGetUniformLocation(shader.GetId(), name.c_str());
    if (loc == -1)
    {
        // put a warning on unexistence of an uniform at location
    }
    return loc;
}

int32_t Uniform::GetUniformLocation(const std::string &name) const
{
    return Uniform::GetUniformLocation(m_Shader, name.c_str());
}