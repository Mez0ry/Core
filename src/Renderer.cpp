#include "Renderer.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#include "Color.hpp"

void Renderer::Clear(uint32_t clear_flags) const{
    glClear(clear_flags);
}

Renderer::~Renderer() {

}

void Renderer::SetClearColor(const Color &color) {
  glClearColor(color.RedF(), color.GreenF(), color.BlueF(), color.AlphaF());
}

void Renderer::Render(const VertexArray &va, const IndexBuffer &ib, const Shader &shader, GLenum mode){
    shader.UseShader();
    va.Bind();
    ib.Bind();
    glDrawElements(mode, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::SwapBuffers(Window &window)
{
    glfwSwapBuffers(window);
}
