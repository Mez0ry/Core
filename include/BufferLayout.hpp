#ifndef __VERTEX_BUFFER_LAYOUT_HPP__
#define __VERTEX_BUFFER_LAYOUT_HPP__
#include <vector>
#include <cstdint>
#include <optional>

#include <glad/gl.h>
#include "Vertex.hpp"

struct LayoutElement{
    LayoutElement(uint32_t _type, uint32_t _count, bool _normalized) : type(_type), count(_count), normalized(_normalized) {}
    uint32_t type, count;
    bool normalized;
};

class BufferLayout{
private:
    std::vector<LayoutElement> m_BufferLayout;
    std::vector<uint32_t> m_Offsets;
    uint32_t m_Stride{0};
public:
    template <typename TValue>
    void Push(bool normalized);

    template <typename TValue>
    void Push(uint32_t count, bool normalized = false);

    uint32_t GetStride() const;

    uint32_t GetStride(const uint32_t count, const uint32_t type) const;
    uint32_t GetStride(const LayoutElement& layout_element) const;

    uint32_t GetStrideAt(const uint32_t index) const;

    std::optional<uint32_t> GetOffset(const int index) const;

    auto begin() const {return m_BufferLayout.cbegin();}
    auto end() const {return m_BufferLayout.cend();}

    const auto& GetElements() const {
        return m_BufferLayout;
    }

private:
    template <typename TValue>
    static auto GetSize(uint32_t count);
};

template <typename TValue>
auto BufferLayout::GetSize(uint32_t count){
    return count * sizeof(TValue);
}

template <typename TValue>
inline void BufferLayout::Push(bool normalized){
    static_assert(std::is_same<TValue, void>::value, "Unsupported type");
}

template <typename TValue>
inline void BufferLayout::Push(uint32_t count, bool normalized){
    static_assert(std::is_same<TValue, void>::value, "Unsupported type");
}

template <>
inline void BufferLayout::Push<float>(uint32_t count, bool normalized){
    m_BufferLayout.push_back({GL_FLOAT, count, normalized});
    auto size = GetSize<float>(count);
    m_Offsets.push_back((m_Offsets.empty()) ? size : m_Offsets.back() + size);
    m_Stride += size;
}

template <>
inline void BufferLayout::Push<uint8_t>(uint32_t count, bool normalized){
    m_BufferLayout.push_back({GL_UNSIGNED_BYTE, count, normalized});
    auto size = GetSize<uint8_t>(count);
    m_Offsets.push_back((m_Offsets.empty()) ? size : m_Offsets.back() + size);
    m_Stride += size;
}

template <>
inline void BufferLayout::Push<uint16_t>(uint32_t count, bool normalized){
    m_BufferLayout.push_back({GL_UNSIGNED_SHORT, count, normalized});
    auto size = GetSize<uint16_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}

template <>
inline void BufferLayout::Push<uint32_t>(uint32_t count, bool normalized){
    m_BufferLayout.push_back({GL_UNSIGNED_INT, count, normalized});
    auto size = GetSize<uint32_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}

template <>
inline void BufferLayout::Push<int8_t>(uint32_t count, bool normalized){
    m_BufferLayout.push_back({GL_BYTE, count, normalized});
    auto size = GetSize<int8_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}

template <>
inline void BufferLayout::Push<int16_t>(uint32_t count, bool normalized){
    m_BufferLayout.push_back({GL_SHORT, count, normalized});
    auto size = GetSize<int16_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}

template <>
inline void BufferLayout::Push<int32_t>(uint32_t count, bool normalized){
    m_BufferLayout.push_back({GL_INT, count, normalized});
    auto size = GetSize<int32_t>(count);
    m_Offsets.push_back((m_Offsets.empty()) ? size : m_Offsets.back() + size);
    m_Stride += size;
}

template <>
inline void BufferLayout::Push<glm::vec<4, float, glm::packed_highp>>(bool normalized){
    this->Push<float>(4, normalized);
}

template <>
inline void BufferLayout::Push<glm::vec<2, float, glm::packed_highp>>(bool normalized){
    this->Push<float>(2, normalized);
}

template <>
inline void BufferLayout::Push<glm::vec<3, float, glm::packed_highp>>(bool normalized){
    this->Push<float>(3, normalized);
}

template <>
inline void BufferLayout::Push<Vertex2D>(bool normalized){
    this->Push<glm::vec2>(normalized);
    this->Push<glm::vec3>(normalized);
    this->Push<glm::vec2>(normalized);
    this->Push<glm::vec3>(normalized);
    this->Push<glm::vec3>(normalized);
}

#endif //!__VERTEX_BUFFER_LAYOUT_HPP__