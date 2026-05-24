#include "BufferLayout.hpp"

const uint32_t BufferLayout::GetStride() const
{
    return m_Stride; 
}

std::optional<uint32_t> BufferLayout::GetStride(const uint32_t count, const uint32_t type) const
{
    uint32_t type_size;

    switch (type)
    {
        case GL_FLOAT:
            type_size = sizeof(float);
            break;
        case GL_UNSIGNED_INT:
            type_size = sizeof(unsigned int);
            break;
        case GL_INT:
            type_size = sizeof(int);
            break;
        case GL_UNSIGNED_BYTE:
            type_size = sizeof(unsigned char);
            break;
        case GL_BYTE:
            type_size = sizeof(char);
            break;
        case GL_DOUBLE:
            type_size = sizeof(double);
            break;
        default:
            return std::nullopt;
    }

    return count * type_size;
}

std::optional<uint32_t> BufferLayout::GetStride(const LayoutElement &layout_element) const
{
    return GetStride(layout_element.count, layout_element.type);
}

std::optional<uint32_t> BufferLayout::GetStrideAt(const uint32_t index) const
{
    return GetStride(m_BufferLayout[index]);
}

std::optional<uint32_t> BufferLayout::GetOffset(const int index) const
{
    if(index >= m_BufferLayout.size()){
        return std::nullopt;
    }

    if(index == 0){
        return 0U;
    }
    
    return m_Offsets[index - 1];
}

const std::vector<LayoutElement> &BufferLayout::GetElements() const
{
    return m_BufferLayout;
}

bool BufferLayout::IsEmpty() const
{
    return (m_Stride == 0);
}

std::optional<uint32_t> BufferLayout::GetElementSizeAt(const int index) const
{
    if(index >= m_BufferLayout.size()){
        return std::nullopt;
    }

    if(m_BufferLayout.size() < 2){
        return m_Stride;
    }

    const auto lhs = m_Offsets[index - 1];

    return ((lhs + m_Offsets[index]) - lhs);
}
