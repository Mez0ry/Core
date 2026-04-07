#include "IndexBuffer.hpp"
#include <glad/gl.h>

IndexBuffer::IndexBuffer(const uint32_t *data, uint32_t element_count) : m_Count(element_count)
{
    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_BufferId);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
}

void IndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t IndexBuffer::GetCount() const
{
    return m_Count;
}
