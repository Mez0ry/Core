#ifndef __VERTEX_ARRAY_HPP__
#define __VERTEX_ARRAY_HPP__
#include <glad/gl.h>
#include <cstdint>

class VertexBuffer;
class BufferLayout;

class VertexArray{
private:
    std::uint32_t m_BufferId;
public:
    VertexArray();
    ~VertexArray();
    
    void AddBuffer(const BufferLayout& layout);
    void Bind() const;
    void UnBind() const;
private:
};
#endif //!__VERTEX_ARRAY_HPP__