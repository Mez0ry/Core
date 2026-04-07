#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__
#include <cstdint>

class VertexBuffer{
private:
    uint32_t m_BufferId;
public:
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer() = default;

    void Bind() const;
    void UnBind() const;
private:
};
#endif //!__VERTEX_BUFFER_HPP__