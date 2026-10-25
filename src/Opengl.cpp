#include "Opengl.hpp"
#include <glad/gl.h>

void gl::EnableAttrib(const uint32_t index) {
    glEnableVertexAttribArray(index);
}

void gl::Enable(GLenum flag) {
    glEnable(flag);
}

void gl::Disable(GLenum flag) {
    glDisable(flag);
}

void gl::VertexAttribPointer(uint32_t index, uint32_t size, uint32_t type, bool normalized, int32_t stride, const void *pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void gl::AllocateBuffer(uint32_t &id, uint32_t amount)
{
    glGenBuffers(amount, &id);
}

void gl::DeleteBuffer(uint32_t &id, uint32_t amount)
{
    glDeleteBuffers(amount, &id);
}

void gl::BindBufferBase(const BufferTarget target, uint32_t location, const uint32_t id) {
    glBindBufferBase(internal::ConvertEnumTo(target), location, id);
}

void gl::Bind(const BufferTarget target, const uint32_t id) {
    glBindBuffer(internal::ConvertEnumTo(target), id);
}

void gl::UnBind(const BufferTarget target) {
    glBindBuffer(internal::ConvertEnumTo(target), 0);
}

void gl::BufferData(const BufferTarget target, size_t size, const void *data, BufferHint hint)
{
    glBufferData(internal::ConvertEnumTo(target), size, data, internal::ConvertEnumTo(hint));
}
