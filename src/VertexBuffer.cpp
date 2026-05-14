#include "VertexBuffer.hpp"
#include <glad/gl.h>
#include "Vertex.hpp"

VertexBuffer::VertexBuffer(const std::initializer_list<Vertex2D> &vertex)
{
    std::vector<Vertex2D> verticies(vertex);

    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex2D), verticies.data(), GL_STATIC_DRAW);

}

VertexBuffer::VertexBuffer(const Vertex2D &vertex) {
    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D), &vertex, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const void *data, uint32_t size) {
  glGenBuffers(1, &m_BufferId);
  glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}

void VertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
