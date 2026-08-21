#include "VertexBuffer.hpp"
#include <glad/gl.h>
#include "Vertex.hpp"

VertexBuffer::VertexBuffer(const std::vector<Vertex2D> &vertices)
{
    GenerateAndBindBuffer();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const std::initializer_list<Vertex2D> &vertices_list)
{
    GenerateAndBindBuffer();

    std::vector<Vertex2D> vertices(vertices_list);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const Vertex2D &vertex) {
    GenerateAndBindBuffer();
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D), &vertex, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const void *data, uint32_t size) {
  GenerateAndBindBuffer();
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_BufferId);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}

void VertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::GenerateAndBindBuffer() {
    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}
