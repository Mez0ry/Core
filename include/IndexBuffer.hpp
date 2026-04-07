#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__
#include <cstdint>

class IndexBuffer{
private:
    uint32_t m_BufferId, m_Count;
public:
    IndexBuffer(const uint32_t* data, uint32_t element_count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    uint32_t GetCount() const;
private:
};
#endif //!__INDEX_BUFFER_HPP__