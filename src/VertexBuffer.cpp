#include "VertexBuffer.hpp"
#include <glad/gl.h>

VertexBuffer::VertexBuffer(const void *data, uint32_t size)
{
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
