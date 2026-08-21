#include "Mesh.hpp"
#include "BufferLayout.hpp"
#include "VertexBuffer.hpp"

Mesh::Mesh(const Ref<VertexArray> va, const Ref<IndexBuffer> ib) : m_VertexArray(va), m_IndexBuffer(ib)
{

}

Mesh::Mesh(const Ref<VertexArray> va, const Ref<IndexBuffer> ib, const std::vector<MeshTexture> &textures) : m_VertexArray(va), m_IndexBuffer(ib), m_Textures(textures)
{
}

const Ref<VertexArray> Mesh::GetVertexArray() const
{
    return m_VertexArray;
}

const Ref<IndexBuffer> Mesh::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

const std::vector<MeshTexture> Mesh::GetTextures() const
{
    return m_Textures;
}

Mesh QuadMesh::BuildQuadMesh(std::vector<MeshTexture> textures) const
{
    BufferLayout vb_layout;
    vb_layout.Push<Vertex2D>(false);

    std::vector<Vertex2D> vertices_pixel{
        Vertex2D(glm::vec2(-0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)),
        Vertex2D(glm::vec2(0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.0f, 0.0f)),
        Vertex2D(glm::vec2(0.5f, 0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.0f, 1.0f)),
        Vertex2D(glm::vec2(-0.5f, 0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.0f, 1.0f))
    };

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    return Mesh(MakeReference<VertexArray>(MakeReference<VertexBuffer>(vertices_pixel), vb_layout), MakeReference<IndexBuffer>(indicies, 6), textures);
}

QuadMesh::QuadMesh(std::vector<MeshTexture> textures) : Mesh(BuildQuadMesh(textures))
{
    
}
