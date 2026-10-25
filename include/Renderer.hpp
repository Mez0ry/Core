#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__
#include <glad/gl.h>
#include "Base.hpp"

BASE_FWD_DECLARE_CLASS(VertexArray);
BASE_FWD_DECLARE_CLASS(IndexBuffer);
BASE_FWD_DECLARE_CLASS(Shader);
BASE_FWD_DECLARE_CLASS(Color);
BASE_FWD_DECLARE_CLASS(Window);
BASE_FWD_DECLARE_CLASS(Mesh);
BASE_FWD_DECLARE_CLASS(Sprite2D);
BASE_FWD_DECLARE_CLASS(Batch);
BASE_FWD_DECLARE_CLASS(SpriteBatch);

class Renderer{
private:
public:
    Renderer() = default;
    ~Renderer();

    void SetClearColor(const Color& color);
    void Clear(uint32_t clear_flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) const;

    void Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum render_mode = GL_TRIANGLES, uint32_t data_type = GL_UNSIGNED_INT);

    void Render(const Ref<Mesh> mesh, const Shader& shader, GLenum render_mode = GL_TRIANGLES, uint32_t data_type = GL_UNSIGNED_INT);
    void Render(const Sprite2D& sprite);
    void Render(SpriteBatch &batch);
    void SwapBuffers(Window& window);
private:
};
#endif //!__RENDERER_HPP__