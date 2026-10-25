#ifndef __OPENGL_UTILS_HPP__
#define __OPENGL_UTILS_HPP__
#include <cstdint>

enum class BufferHint : uint32_t {
    StaticDraw  = 0x88E4,
    DynamicDraw = 0x88E8,
    StreamDraw  = 0x88E0
};

enum class BufferTarget : uint32_t {
    Array            = 0x8892, // GL_ARRAY_BUFFER
    ElementArray     = 0x8893, // GL_ELEMENT_ARRAY_BUFFER
    CopyRead         = 0x8F36, // GL_COPY_READ_BUFFER
    CopyWrite        = 0x8F37, // GL_COPY_WRITE_BUFFER
    PixelPack        = 0x88EB, // GL_PIXEL_PACK_BUFFER
    PixelUnpack      = 0x88EC, // GL_PIXEL_UNPACK_BUFFER
    TransformFeedback = 0x8C8E, // GL_TRANSFORM_FEEDBACK_BUFFER
    Uniform          = 0x8A11, // GL_UNIFORM_BUFFER
    Texture          = 0x8C2A, // GL_TEXTURE_BUFFER
    DrawIndirect     = 0x8F3F, // GL_DRAW_INDIRECT_BUFFER
    DispatchIndirect = 0x90EE, // GL_DISPATCH_INDIRECT_BUFFER
    AtomicCounter    = 0x92C0, // GL_ATOMIC_COUNTER_BUFFER
    ShaderStorage    = 0x90D2, // GL_SHADER_STORAGE_BUFFER
    Query            = 0x9192  // GL_QUERY_BUFFER
};

namespace internal{
    template <typename TEnum>
    constexpr uint32_t ConvertEnumTo(TEnum target) {
        return static_cast<uint32_t>(target);
    }

}

namespace gl{
    void EnableAttrib(const uint32_t index);
    void Enable(const uint32_t gl_flag);
    
    void Disable(const uint32_t gl_flag);

    void VertexAttribPointer(uint32_t index,  uint32_t size, uint32_t type, bool normalized, int32_t stride, const void* pointer);

#pragma region Buffers
    /**
     * @brief Generates buffer
    */
    void AllocateBuffer(uint32_t& id, uint32_t amount = 1);
    void DeleteBuffer(uint32_t& id, uint32_t amount = 1);

    void BindBufferBase(const BufferTarget target, uint32_t location, const uint32_t id);

    void Bind(const BufferTarget target, const uint32_t id);
    void UnBind(const BufferTarget target);

    void BufferData(const BufferTarget target, size_t size, const void* data, BufferHint hint);
#pragma endregion

};
#endif //!__OPENGL_UTILS_HPP__