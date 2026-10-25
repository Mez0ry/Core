#ifndef __VERTEX_ARRAY_HPP__
#define __VERTEX_ARRAY_HPP__
#include <glad/gl.h>
#include <cstdint>
#include "Base.hpp"

#include <vector>

BASE_FWD_DECLARE_CLASS(LayoutElement);
BASE_FWD_DECLARE_CLASS(VertexBuffer);
BASE_FWD_DECLARE_CLASS(BufferLayout);

class VertexArray{
private:
    std::uint32_t m_BufferId;
    Ref<VertexBuffer> m_LastUsedVertexBuffer;
    std::vector<LayoutElement> m_Elements;
    size_t m_Location{0};
public:
    VertexArray();
    VertexArray(const Ref<VertexBuffer> vertex_buffer, const BufferLayout& layout);
    ~VertexArray();
    
    void AddBuffer(const VertexBuffer& vertex_buffer, const BufferLayout& layout);
    void Bind() const;
    void UnBind() const;

    Ref<VertexBuffer> GetVertexBuffer() const;

private:
};
#endif //!__VERTEX_ARRAY_HPP__