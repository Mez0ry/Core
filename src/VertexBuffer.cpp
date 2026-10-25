#include "VertexBuffer.hpp"
#include <glad/gl.h>
#include "Vertex.hpp"

VertexBuffer::VertexBuffer(const std::vector<Vertex2D> &vertices, BufferHint hint)
{
    GenerateAndBindBuffer();
    gl::BufferData(BufferTarget::Array, vertices.size() * sizeof(Vertex2D), vertices.data(), hint);
}

VertexBuffer::VertexBuffer(const std::initializer_list<Vertex2D> &vertices_list, BufferHint hint) : VertexBuffer(std::vector<Vertex2D>(vertices_list))
{
   
}

VertexBuffer::VertexBuffer(const Vertex2D &vertex, BufferHint hint) : m_Hint(hint){
    GenerateAndBindBuffer();
    gl::BufferData(BufferTarget::Array, sizeof(Vertex2D), &vertex, hint);
}


VertexBuffer::VertexBuffer(const std::vector<glm::mat4>& mats, BufferHint hint) : m_Hint(hint){
    GenerateAndBindBuffer();
    gl::BufferData(BufferTarget::Array, mats.size() * sizeof(glm::mat4), mats.data(), hint);
}

VertexBuffer::VertexBuffer(const std::initializer_list<glm::mat4>& mat_list, BufferHint hint) : VertexBuffer(std::vector<glm::mat4>(mat_list), hint) {

}

VertexBuffer::VertexBuffer(const void *data, uint32_t size, BufferHint hint) {
  GenerateAndBindBuffer();
  gl::BufferData(BufferTarget::Array, size, data, hint);
}

VertexBuffer::~VertexBuffer() {
    gl::DeleteBuffer(m_BufferId);
}

void VertexBuffer::Bind() const {
    gl::Bind(BufferTarget::Array, m_BufferId);
}

void VertexBuffer::UnBind() const {
    gl::Bind(BufferTarget::Array, 0);
}

void VertexBuffer::GenerateAndBindBuffer() {
    gl::AllocateBuffer(m_BufferId);
    gl::Bind(BufferTarget::Array, m_BufferId);
}
