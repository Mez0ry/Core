#include "Mesh.hpp"

Mesh::Mesh(const VertexArray &va, const IndexBuffer &ib, Shader &&shader) : m_VertexArray(va), m_IndexBuffer(ib), m_Shader(std::move(shader))
{

}
