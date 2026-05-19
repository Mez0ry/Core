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

void VertexArray::AddBuffer(const VertexBufferLayout &layout)
{
    Bind();

    const auto& elements = layout.GetElements();
    
    for(auto index = 0; index < elements.size(); index++){
        auto& element = elements[index];
        const auto optional_offset = (index == 0) ? 0 : layout.GetOffset(index - 1);
        const auto offset = (const void*)static_cast<uintptr_t>((optional_offset.has_value()) ? optional_offset.value() : 0);

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.count, element.type, element.normalized, layout.GetStride(), offset);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_BufferId);
}

void VertexArray::UnBind() const {
    glBindVertexArray(0);
}
