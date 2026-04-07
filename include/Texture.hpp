#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
#include <cstdint>
#include <string>
#include <memory>
#include "Base.hpp"
#include <glad/gl.h>

class Texture{
private:
    uint32_t m_TextureId{0};
    const std::string m_Path;
    Ref<uint8_t> m_LocalBuffer{nullptr};
    std::int32_t m_Width{0}, m_Height{0}, m_BasePerPixel{0};
public:
    Texture(const std::string& path, GLenum pixel_data_type = GL_UNSIGNED_BYTE, int32_t wrapping = GL_CLAMP_TO_EDGE, int32_t filtering = GL_LINEAR);
    ~Texture();

    [[nodiscard]] Ref<uint8_t> Data() const;

    void Bind(uint32_t slot = 0) const;
    void UnBind() const;

    void FreeBuffer();
    
private:
};
#endif //! __TEXTURE_HPP__