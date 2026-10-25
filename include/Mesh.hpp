#ifndef __MESH_HPP__
#define __MESH_HPP__
#include "Base.hpp"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <vector>

class Mesh{
protected:
    Ref<VertexArray> m_VertexArray;
    Ref<IndexBuffer> m_IndexBuffer;
    Ref<Texture> m_Texture;
    std::vector<Vertex2D> m_Vertices;
public:
    Mesh() = default;
    explicit Mesh(const Ref<VertexArray> va, const Ref<IndexBuffer> ib);
    explicit Mesh(const Ref<VertexArray> va, const Ref<IndexBuffer> ib, const Ref<Texture> texture);

    virtual ~Mesh(){}

    const Ref<VertexArray> GetVertexArray() const;
    const Ref<IndexBuffer> GetIndexBuffer() const;
    const Ref<Texture> GetTexture() const;

    const std::vector<Vertex2D>& GetVertices() const;
protected:
    void Construct(const Ref<VertexArray> va, const Ref<IndexBuffer> ib, Ref<Texture> texture);
};

class QuadMesh final : public Mesh{
public:
    QuadMesh(const Ref<Texture> texture);
};
#endif //!__MESH_HPP__