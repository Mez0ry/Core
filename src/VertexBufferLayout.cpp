#include "VertexBufferLayout.hpp"

uint32_t VertexBufferLayout::GetStride() const
{
    return m_Stride; 
}

std::optional<uint32_t> VertexBufferLayout::GetOffset(const int index) const
{
    return m_Offsets[index];
}
