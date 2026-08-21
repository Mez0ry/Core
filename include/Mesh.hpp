#ifndef __MESH_HPP__
#define __MESH_HPP__
#include "Base.hpp"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <vector>

class VertexArray;
class IndexBuffer; 
class Shader;
class Texture;

enum class TextureType {
    Diffuse,
    Specular,
    Normal,
    Roughness,
    Metalness,
    Base,
};

struct MeshTexture {
    MeshTexture(const Ref<Texture> texture_, TextureType type_) : texture(texture_), type(type_), str_type(TypeToString(type)) {}
    const Ref<Texture> texture;  
    TextureType type;
    std::string str_type;
private:
    std::string TypeToString(TextureType type) const {
        switch (type) {
            case TextureType::Diffuse: return "texture_diffuse";
            case TextureType::Specular: return "texture_specular";
            case TextureType::Normal: return "texture_normal";
            case TextureType::Roughness: return "texture_roughness";
            case TextureType::Metalness: return "texture_metalness";
            case TextureType::Base: return "u_texture";
            default: return "unknown";
        }
    }
};

class Vector2D;

class Mesh{
protected:
    Ref<VertexArray> m_VertexArray;
    Ref<IndexBuffer> m_IndexBuffer;
    std::vector<MeshTexture> m_Textures;
public:
    Mesh() = default;
    explicit Mesh(const Ref<VertexArray> va, const Ref<IndexBuffer> ib);
    explicit Mesh(const Ref<VertexArray> va, const Ref<IndexBuffer> ib, const std::vector<MeshTexture>& textures);

    virtual ~Mesh(){}

    const Ref<VertexArray> GetVertexArray() const;
    const Ref<IndexBuffer> GetIndexBuffer() const;
    const std::vector<MeshTexture> GetTextures() const;
};

class QuadMesh final : public Mesh{
private:
    Mesh BuildQuadMesh(std::vector<MeshTexture> textures) const;
public:
    QuadMesh(std::vector<MeshTexture> textures);
};
#endif //!__MESH_HPP__