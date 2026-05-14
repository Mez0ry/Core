#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__
#include <cstdint>
#include <initializer_list>

struct Vertex2D;

class VertexBuffer{
private:
    uint32_t m_BufferId;
public:
    VertexBuffer(const std::initializer_list<Vertex2D>& vertex);
    VertexBuffer(const Vertex2D& vertex);
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer() = default;

    void Bind() const;
    void UnBind() const;
private:
};
#endif //!__VERTEX_BUFFER_HPP__