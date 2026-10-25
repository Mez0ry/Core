#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__
#include "Base.hpp"

#include <glm/ext.hpp>
#include <cstdint>
#include <initializer_list>
#include <vector>

BASE_FWD_DECLARE_STRUCT(Vertex2D);

class VertexBuffer{
private:
    uint32_t m_BufferId;
    BufferHint m_Hint;
public:
    VertexBuffer() = default;
    
    VertexBuffer(const std::vector<Vertex2D>& vertices, BufferHint hint = BufferHint::StaticDraw);
    VertexBuffer(const std::initializer_list<Vertex2D>& vertices_list, BufferHint hint = BufferHint::StaticDraw);
    VertexBuffer(const Vertex2D& vertex, BufferHint hint = BufferHint::StaticDraw);

    VertexBuffer(const std::vector<glm::mat4>& mat_list, BufferHint hint = BufferHint::DynamicDraw);
    VertexBuffer(const std::initializer_list<glm::mat4>& mat_list, BufferHint hint = BufferHint::DynamicDraw);

    VertexBuffer(const void* data, uint32_t size, BufferHint hint = BufferHint::StaticDraw);

    ~VertexBuffer();
    
    void Bind() const;
    void UnBind() const;
private:
    void GenerateAndBindBuffer();
};
#endif //!__VERTEX_BUFFER_HPP__