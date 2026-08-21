#include "UniformBuffer.hpp"
#include "BufferLayout.hpp"
#include <spdlog/spdlog.h>

UniformBuffer::UniformBuffer(const BufferLayout &layout, const Location location, UniformLayoutType uniform_layout_type) : m_BufferLayout(layout), m_Location(location)
{
    if(layout.IsEmpty()){
        spdlog::error("UniformBuffer creation failed: BufferLayout is empty.");
    }

    glGenBuffers(1, &m_BufferId);
    Bind();
    BindBufferBase(m_Location);

    AllocateData(m_BufferLayout, uniform_layout_type);
    UnBind();
}

void UniformBuffer::Bind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, m_BufferId);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        spdlog::error("OpenGL error during UniformBuffer::Bind: {}", error);
    }
}

void UniformBuffer::BindBufferBase(const Location location) {
    glBindBufferBase(GL_UNIFORM_BUFFER, static_cast<std::uint8_t>(location), m_BufferId);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        spdlog::error("OpenGL error during UniformBuffer::BindBufferBase at location {}: {}", static_cast<int>(location), error);
    }
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
            spdlog::warn("UniformBuffer::AllocateData received unsupported UniformLayoutType");
            break;
        }
    }
}

const size_t UniformBuffer::RoundUpToMultipleOf(size_t size, uint32_t number) const
{
    const size_t remainder = size % number;
    return (remainder == 0) ? size : size + (number - remainder);
}