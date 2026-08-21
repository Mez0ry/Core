#include "Sprite2D.hpp"
#include "Uniform.hpp"

Sprite2D::Sprite2D(const std::string &texture_path, const Ref<Shader> shader, glm::vec2 size, glm::vec2 pos) : m_Model(1.f), m_Mesh({MeshTexture(MakeReference<Texture>(texture_path), TextureType::Base)}), m_Shader(shader), m_Size(size), m_Position(pos)
{
   
}

void Sprite2D::SetPosition(glm::vec2 pos) {
    m_Position = pos;
}

glm::vec2 Sprite2D::GetPosition() const
{
    return m_Position;
}

void Sprite2D::SetRotation(float degrees) {
    m_Rotation = degrees;
}

float Sprite2D::GetRotation() const { 
    return m_Rotation; 
}

void Sprite2D::SetSize(glm::vec2 &size)
{
    m_Size = size;
}

const glm::vec2 &Sprite2D::GetSize() const
{
    return m_Size;
}

void Sprite2D::SetScale(float scale_factor) {
    m_ScaleFactor = scale_factor;
}

float Sprite2D::GetScale() const
{
    return m_ScaleFactor;
}

glm::mat4 Sprite2D::GetModel() const
{
    return m_Model;
}

const QuadMesh& Sprite2D::GetMesh() const
{
    return m_Mesh;
}

const Ref<Shader> Sprite2D::GetShader() const
{
    return m_Shader;
}

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

void Sprite2D::Update() const{
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, {m_Position, 0.f});
    model = glm::translate(model, glm::vec3(0.5f * m_Size.x, 0.5f * m_Size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * m_Size.x, -0.5f * m_Size.y, 0.0f));

    model = glm::scale(model, glm::vec3(m_Size, 1.0f)); 
    
    m_Model = model;
    
    if(m_Shader){
        m_Shader->UseShader();
        Uniform::SetShaderUniformMat4(*m_Shader, "u_Model", model);
        //std::cout << glm::to_string(m_Model) << '\n';
    }
}

void Sprite2D::SetModel(glm::mat4 model_mat) {
    m_Model = model_mat;
}
