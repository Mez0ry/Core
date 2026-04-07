#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <glad/gl.h>

class VertexArray;
class IndexBuffer;
class Shader;
class Color;

class Window;

class Renderer{
private:
public:
    Renderer() = default;
    ~Renderer();

    void SetClearColor(const Color& color);
    void Clear(uint32_t clear_flags = GL_COLOR_BUFFER_BIT) const;

    void Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum mode = GL_TRIANGLES);

    void SwapBuffers(Window& window);
private:
};
#endif //!__RENDERER_HPP__