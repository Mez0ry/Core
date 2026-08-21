#ifndef __UNIFORM_BUFFER_HPP__
#define __UNIFORM_BUFFER_HPP__
#include <cstdint>
#include "BufferLayout.hpp"

class BufferLayout;

enum class UniformLayoutType : uint8_t{
    STD_140
};

enum class Location : uint8_t{
    Camera
};

class UniformBuffer{
private:
    std::uint32_t m_BufferId;
    BufferLayout m_BufferLayout;
    Location m_Location;
public:
    UniformBuffer() = default;
    UniformBuffer(const BufferLayout& layout, const Location location, UniformLayoutType uniform_layout_type = UniformLayoutType::STD_140);

    void Bind() const;
    void BindBufferBase(const Location location);

    void UnBind() const;
    
    template <typename T>
    void StoreData(T value);

    template <typename TRet>
    inline TRet GetData(uint32_t offset = 0U);
    
    void AllocateData(const BufferLayout& layout, UniformLayoutType uniform_layout_type) const;
private:
    const size_t RoundUpToMultipleOf(size_t size, uint32_t number) const;
};

template <typename T>
inline void UniformBuffer::StoreData(T value)
{
    const auto u_loc = static_cast<uint8_t>(m_Location);
    const auto element_size = m_BufferLayout.GetElementSizeAt(u_loc);
    if( !element_size.has_value() || element_size.value() != sizeof(T)){
        // Handle
        return;
    }
    
    this->Bind();
    glBufferSubData(GL_UNIFORM_BUFFER, m_BufferLayout.GetOffset(u_loc).value_or(0), element_size.value(), &value);
    this->UnBind();
}

template <typename TRet>
inline TRet UniformBuffer::GetData(uint32_t offset)
{
    this->Bind();
    TRet ret{};
    glGetBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(TRet), &ret);
    this->UnBind();
    return ret;
}

#endif //!__UNIFORM_BUFFER_HPP__