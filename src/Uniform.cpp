#include "Uniform.hpp"
#include "Shader.hpp"
#include <glad/gl.h>
#include "glm/ext.hpp"

Uniform::Uniform(Shader & shader) : m_Shader(shader)
{
    
}

void Uniform::SetUniformBlock(const Shader &shader, const std::string &block_name, int32_t uniform_block_idx)
{
    shader.UseShader();

    GLuint uniform_block_index = glGetUniformBlockIndex(shader.GetId(), block_name.c_str());

    if (uniform_block_index == GL_INVALID_INDEX)
    {
        //std::cerr << "Uniform block \"" << block_name << "\" not found in shader." << std::endl;
        return;
    }

    glUniformBlockBinding(shader.GetId(), uniform_block_index, uniform_block_idx);
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
    if(shader.IsValid()){
        shader.UseShader();
        int location = Uniform::GetUniformLocation(shader, name);
        if (location == -1)
        {
            //std::cerr << "Warning: Uniform '" << name << "' not found or inactive in shader." << std::endl;
        }
        else
        {
            glUniform1i(location, v0);
            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                //std::cerr << "OpenGL error when setting uniform '" << name << "': " << error << std::endl;
            }
        }
        

    } 
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
    glUniformMatrix4fv(Uniform::GetUniformLocation(shader, name), 1, transpose, glm::value_ptr(mat));
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

uint32_t Uniform::GetUniformBlockIndex(const std::string &name) const
{
   return Uniform::GetUniformBlockIndex(m_Shader, name);
}

uint32_t Uniform::GetUniformBlockIndex(const Shader &shader, const std::string &name)
{
    uint32_t block_index = glGetUniformLocation(shader.GetId(), name.c_str());
    if (block_index == GL_INVALID_INDEX)
    {
        //std::cerr << "Warning: Uniform block '" << name << "' does not exist." << std::endl;
        return GL_INVALID_INDEX;
    }

    return block_index;
}
