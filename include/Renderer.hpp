#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <glad/gl.h>

class VertexArray;
class IndexBuffer;
class Shader;
class Color;

class Window;
class Mesh;
class Sprite2D;

class Renderer{
private:
public:
    Renderer() = default;
    ~Renderer();

    void SetClearColor(const Color& color);
    void Clear(uint32_t clear_flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) const;

    void Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum render_mode = GL_TRIANGLES, uint32_t data_type = GL_UNSIGNED_INT);

    void Render(const Mesh& mesh, const Shader& shader, GLenum render_mode = GL_TRIANGLES, uint32_t data_type = GL_UNSIGNED_INT);
    void Render(const Sprite2D& sprite);
    void SwapBuffers(Window& window);
private:
};
#endif //!__RENDERER_HPP__