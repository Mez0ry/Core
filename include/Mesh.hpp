#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class VertexArray;
class IndexBuffer; 
class Shader;

class Mesh{
private:
    VertexArray m_VertexArray;
    IndexBuffer m_IndexBuffer;
    Shader m_Shader;
public:
    explicit Mesh(const VertexArray &va, const IndexBuffer &ib, Shader &&shader);
private:
};
#endif //!__MESH_HPP__