#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_BufferId);  
    Bind();
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_BufferId);
}

void VertexArray::AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout)
{
    Bind();

    const auto& elements = layout.GetElements();

    for(auto index = 0; index < elements.size(); index++){
        auto& element = elements[index];
        const auto stride = layout.GetStride();
        const auto optional_offset = layout.GetOffset(index);
  
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.count, element.type, element.normalized, stride, (const void*)static_cast<uintptr_t>((optional_offset.has_value()) ? optional_offset.value(): 0));
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_BufferId);
}

void VertexArray::UnBind() const {
    glBindVertexArray(0);
}
