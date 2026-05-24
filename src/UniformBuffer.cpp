#include "UniformBuffer.hpp"
#include "BufferLayout.hpp"

UniformBuffer::UniformBuffer(const BufferLayout &layout, const Location location, UniformLayoutType uniform_layout_type) : m_BufferLayout(layout)
{
    if(layout.IsEmpty()){
        // handle it
    }

    glGenBuffers(1, &m_BufferId);
    Bind();
    glBindBufferBase(GL_UNIFORM_BUFFER, static_cast<std::uint8_t>(m_Location), m_BufferId);

    AllocateData(m_BufferLayout, uniform_layout_type);
    UnBind();
}

void UniformBuffer::Bind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, m_BufferId);
}

void UniformBuffer::UnBind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::AllocateData(const BufferLayout &layout, UniformLayoutType uniform_layout_type) const
{
    switch(uniform_layout_type){
        case UniformLayoutType::STD_140:{
            const size_t data_size{RoundUpToMultipleOf(m_BufferLayout.GetStride(), 16)};
            glBufferData(GL_UNIFORM_BUFFER, data_size, NULL, GL_STATIC_DRAW);
            break;
        }

        default:{
            break;
        }
    }

}

const size_t UniformBuffer::RoundUpToMultipleOf(size_t size, uint32_t number) const
{
    const size_t remainder = size % number;
    return (remainder == 0) ? size : size + (number - remainder);
}