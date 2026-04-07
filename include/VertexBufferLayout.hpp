#ifndef __VERTEX_BUFFER_LAYOUT_HPP__
#define __VERTEX_BUFFER_LAYOUT_HPP__
#include <vector>
#include <cstdint>
#include <optional>

#include <glad/gl.h>

struct LayoutElement{
    LayoutElement(uint32_t _type, uint32_t _count, bool _normalized) : type(_type), count(_count), normalized(_normalized) {}
    uint32_t type, count;
    bool normalized;
};

class VertexBufferLayout{
private:
    std::vector<LayoutElement> m_VertexBufferLayout;
    std::vector<uint32_t> m_Offsets;
    uint32_t m_Stride{0};
public:
    template <typename TValue>
    void Push(uint32_t count, bool normalized = false);

    uint32_t GetStride() const;
    std::optional<uint32_t> GetOffset(const int index) const;

    auto begin() const {return m_VertexBufferLayout.cbegin();}
    auto end() const {return m_VertexBufferLayout.cend();}

    const auto& GetElements() const {
        return m_VertexBufferLayout;
    }

private:
    template <typename TValue>
    static auto GetSize(uint32_t count);
};

template <typename TValue>
auto VertexBufferLayout::GetSize(uint32_t count){
    return count * sizeof(TValue);
}

template <typename TValue>
inline void VertexBufferLayout::Push(uint32_t count, bool normalized){
    static_assert(std::is_same<TValue, void>::value, "Unsupported type");
}
template <>
inline void VertexBufferLayout::Push<float>(uint32_t count, bool normalized){
    auto buffer_was_empty = m_VertexBufferLayout.empty();

    m_VertexBufferLayout.push_back({GL_FLOAT, count, normalized});
    auto size = GetSize<float>(count);
    m_Offsets.push_back((buffer_was_empty) ? !buffer_was_empty : size);
    m_Stride += size;
}

template <>
inline void VertexBufferLayout::Push<uint8_t>(uint32_t count, bool normalized){
    auto buffer_was_empty = m_VertexBufferLayout.empty();
    m_VertexBufferLayout.push_back({GL_UNSIGNED_BYTE, count, normalized});
    auto size = GetSize<uint8_t>(count);
    m_Offsets.push_back((buffer_was_empty) ? buffer_was_empty : size);
    m_Stride += size;
}

template <>
inline void VertexBufferLayout::Push<uint16_t>(uint32_t count, bool normalized){
    m_VertexBufferLayout.push_back({GL_UNSIGNED_SHORT, count, normalized});
    auto size = GetSize<uint16_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}

template <>
inline void VertexBufferLayout::Push<uint32_t>(uint32_t count, bool normalized){
    m_VertexBufferLayout.push_back({GL_UNSIGNED_INT, count, normalized});
    auto size = GetSize<uint32_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}

template <>
inline void VertexBufferLayout::Push<int8_t>(uint32_t count, bool normalized){
    m_VertexBufferLayout.push_back({GL_BYTE, count, normalized});
    auto size = GetSize<int8_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}

template <>
inline void VertexBufferLayout::Push<int16_t>(uint32_t count, bool normalized){
    m_VertexBufferLayout.push_back({GL_SHORT, count, normalized});
    auto size = GetSize<int16_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}

template <>
inline void VertexBufferLayout::Push<int32_t>(uint32_t count, bool normalized){
    m_VertexBufferLayout.push_back({GL_INT, count, normalized});
    auto size = GetSize<int32_t>(count);
    m_Offsets.push_back(size);
    m_Stride += size;
}
#endif //!__VERTEX_BUFFER_LAYOUT_HPP__