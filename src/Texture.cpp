#include "Texture.hpp"
#include <stb_image.h>
#include <functional>

Texture::Texture(const std::string &path, GLenum pixel_data_type, int32_t wrapping, int32_t filtering ) : m_Path(path)
{
    stbi_set_flip_vertically_on_load(true);
    auto img_data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BasePerPixel, 4);
     if(!img_data){
        // handle
        return;
    }

    m_LocalBuffer = Ref<uint8_t>(img_data, [](uint8_t* data){
        if(!data){
            return;
        }
        stbi_image_free(data);
    });
    
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

    auto format = (m_BasePerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, format, pixel_data_type, m_LocalBuffer.get());
    
    UnBind();
}

Texture::~Texture() {
    glDeleteTextures(1, &m_TextureId);
}

Ref<uint8_t> Texture::Data() const
{
    return m_LocalBuffer;
}

void Texture::Bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Texture::UnBind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::FreeBuffer() {
    m_LocalBuffer.reset();
}
