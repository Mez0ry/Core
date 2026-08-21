#ifndef __VERTEX_ARRAY_HPP__
#define __VERTEX_ARRAY_HPP__
#include <glad/gl.h>
#include <cstdint>
#include "Base.hpp"

class VertexBuffer;
class BufferLayout;

class VertexArray{
private:
    std::uint32_t m_BufferId;
    Ref<VertexBuffer> m_LastUsedVertexBuffer;
public:
    VertexArray();
    VertexArray(const Ref<VertexBuffer> vertex_buffer, const BufferLayout& layout);
    ~VertexArray();
    
    void AddBuffer(const VertexBuffer& vertex_buffer, const BufferLayout& layout);
    void Bind() const;
    void UnBind() const;
private:
};
#endif //!__VERTEX_ARRAY_HPP__