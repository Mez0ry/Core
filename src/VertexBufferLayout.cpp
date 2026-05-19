#include "VertexBufferLayout.hpp"

uint32_t VertexBufferLayout::GetStride() const
{
    return m_Stride; 
}

uint32_t VertexBufferLayout::GetStride(const uint32_t count, const uint32_t type) const
{
    uint32_t type_size{std::numeric_limits<uint32_t>::max()};

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
            return 0;
    }

    return count * type_size;
}

uint32_t VertexBufferLayout::GetStride(const LayoutElement &layout_element) const
{
    return GetStride(layout_element.count, layout_element.type);
}

uint32_t VertexBufferLayout::GetStrideAt(const uint32_t index) const
{
    if(index >= m_VertexBufferLayout.size()){
        return std::numeric_limits<uint32_t>::max();
    }

    return GetStride(m_VertexBufferLayout[index]);
}

std::optional<uint32_t> VertexBufferLayout::GetOffset(const int index) const
{
    return m_Offsets[index];
}
