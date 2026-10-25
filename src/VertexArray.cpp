#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "BufferLayout.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_BufferId);  
    Bind();
}

VertexArray::VertexArray(const Ref<VertexBuffer> vertex_buffer, const BufferLayout &layout)
{
    glGenVertexArrays(1, &m_BufferId);  
    Bind();
    m_LastUsedVertexBuffer = vertex_buffer;

    if(m_LastUsedVertexBuffer)
        AddBuffer(*m_LastUsedVertexBuffer, layout);
    
    UnBind();
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_BufferId);
}

void VertexArray::AddBuffer(const VertexBuffer& buffer, const BufferLayout &layout)
{
    Bind();
    buffer.Bind();
    const auto& elements = layout.GetElements();
    
    m_Elements.insert(m_Elements.end(), elements.begin(), elements.end());

    for(;m_Location < m_Elements.size(); ++m_Location){
        auto& element = m_Elements[m_Location];
        const auto offset_value = layout.GetOffset(m_Location).value_or(0);
        const auto offset_casted = (const void*)static_cast<uintptr_t>(offset_value);

        switch(element.shader_dt){
            case ShaderDataType::FLOAT:{
                gl::EnableAttrib(m_Location);
                glVertexAttribPointer(m_Location, element.count, element.gl_type, element.normalized, layout.GetStride(), offset_casted);
                break;
            }
            case ShaderDataType::MAT4:{
                	for (GLuint count = 0; count < element.GetComponentCount(); ++count) {
                        GLuint component_location = static_cast<GLuint>(m_Location) + count;
                        gl::EnableAttrib(component_location);
                        gl::VertexAttribPointer(
                            component_location,
                            element.GetComponentCount(),
                            element.gl_type,
                            element.normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(),
                            reinterpret_cast<const void*>(static_cast<uintptr_t>(offset_value + count * sizeof(glm::vec4))));
                        glVertexAttribDivisor(component_location, 1);
                    }
                break;
            }
        }
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_BufferId);
}

void VertexArray::UnBind() const {
    glBindVertexArray(0);
}

Ref<VertexBuffer> VertexArray::GetVertexBuffer() const
{
    return m_LastUsedVertexBuffer;
}
