#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

#include <cstdint>
#include <initializer_list>
#include <vector>

struct Vertex2D;

class VertexBuffer{
private:
    uint32_t m_BufferId;
public:
    VertexBuffer(const std::vector<Vertex2D>& vertices);
    VertexBuffer(const std::initializer_list<Vertex2D>& vertices_list);
    VertexBuffer(const Vertex2D& vertex);
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer();
    
    void Bind() const;
    void UnBind() const;
private:
    void GenerateAndBindBuffer();
};
#endif //!__VERTEX_BUFFER_HPP__