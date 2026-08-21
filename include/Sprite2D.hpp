#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__
#include "Mesh.hpp"
#include <glm/ext.hpp>
#include <string>

class Sprite2D{
private:
    mutable glm::mat4 m_Model;
    QuadMesh m_Mesh;
    Ref<Shader> m_Shader;
public:
    enum class Location : int{
        U_TEXTURE = 0, 
        U_TEXTURE_DIFFUSE1, U_TEXTURE_DIFFUSE2, U_TEXTURE_DIFFUSE3,
        U_TEXTURE_NORMAL1, U_TEXTURE_NORMAL2, U_TEXTURE_NORMAL3 
    };
    Sprite2D(const std::string& texture_path, const Ref<Shader> shader, glm::vec2 size, glm::vec2 pos = {0, 0});
    ~Sprite2D() = default;

    void SetPosition(glm::vec2 pos);
    glm::vec2 GetPosition() const;
    
    void SetRotation(float degrees);
    float GetRotation() const;

    void SetSize(glm::vec2& size);
    const glm::vec2& GetSize() const;

    void SetScale(float scale_factor);
    float GetScale() const;

    glm::mat4 GetModel() const;
    const QuadMesh& GetMesh() const;
    const Ref<Shader> GetShader() const;

    void Update() const;
private:
    void SetModel(glm::mat4 model_mat);
private:
    glm::vec2 m_Position;
    glm::vec2 m_Size;
    float m_Rotation{0};
    float m_ScaleFactor{1.0f};
};
#endif //!__SPRITE_HPP__