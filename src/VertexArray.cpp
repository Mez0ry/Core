#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "BufferLayout.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_BufferId);  
    Bind();
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_BufferId);
}

void VertexArray::AddBuffer(const BufferLayout &layout)
{
    Bind();

    const auto& elements = layout.GetElements();
    
    for(auto index = 0; index < elements.size(); index++){
        auto& element = elements[index];
        const auto offset = (const void*)static_cast<uintptr_t>(layout.GetOffset(index).value_or(0));

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
