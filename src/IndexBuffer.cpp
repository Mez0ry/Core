#include "IndexBuffer.hpp"
#include <glad/gl.h>
#include "Base.hpp"

IndexBuffer::IndexBuffer(const uint32_t *data, uint32_t element_count) : m_Count(element_count)
{
    CreateBuffer(data, element_count);
}

IndexBuffer::~IndexBuffer() {
    gl::DeleteBuffer(m_BufferId);
}

void IndexBuffer::CreateBuffer(const uint32_t *data, uint32_t element_count)
{
    gl::AllocateBuffer(m_BufferId);
    gl::Bind(BufferTarget::ElementArray, m_BufferId);
    gl::BufferData(BufferTarget::ElementArray, element_count * sizeof(uint32_t), data, BufferHint::StaticDraw);
}

void IndexBuffer::Bind() const
{
    gl::Bind(BufferTarget::ElementArray, m_BufferId);
}

void IndexBuffer::UnBind() const {
    gl::UnBind(BufferTarget::ElementArray);
}

uint32_t IndexBuffer::GetCount() const
{
    return m_Count;
}
