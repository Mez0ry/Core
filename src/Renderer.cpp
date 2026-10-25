#include "Renderer.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#include "IndexBuffer.hpp"
#include "Shader.hpp"

#include "Mesh.hpp"
#include "Uniform.hpp"
#include "Sprite2D.hpp"
#include "Batch.hpp"

#include "Color.hpp"

#include <spdlog/spdlog.h>

void Renderer::Clear(uint32_t clear_flags) const{
    glClear(clear_flags);
}

Renderer::~Renderer() {

}

void Renderer::SetClearColor(const Color &color) {
  glClearColor(color.RedF(), color.GreenF(), color.BlueF(), color.AlphaF());
}

void Renderer::Render(const VertexArray &va, const IndexBuffer &ib, const Shader &shader, GLenum render_mode, uint32_t data_type){
    shader.UseShader();
    va.Bind();
    ib.Bind();

    glDrawElements(render_mode, ib.GetCount(), data_type, nullptr);
    
    va.UnBind();
    ib.UnBind();
}

void Renderer::Render(const Ref<Mesh> mesh, const Shader &shader, GLenum render_mode, uint32_t data_type)
{
    if(!mesh){
        spdlog::warn("Core::Renderer:Render(const Ref<Mesh>, const Shader&, GLenum, uint32_t), Warning: Mesh is nullptr");
        return;
    }

    if(!shader.IsValid()){
        spdlog::warn("Core::Renderer:Render(const Ref<Mesh>, const Shader&, GLenum, uint32_t), Warning: Shader is not valid");
        return;
    }

    shader.UseShader();
    
    auto texture = mesh->GetTexture();
    texture->Bind();
    Uniform::SetShaderUniformInt1(shader, "u_texture", 0);

    auto& va = mesh->GetVertexArray();
    auto& ib = mesh->GetIndexBuffer();
    va->Bind();
    ib->Bind();
    
    glDrawElements(render_mode, ib->GetCount(), data_type, nullptr);
    va->UnBind();

    glActiveTexture(GL_TEXTURE0);
}

void Renderer::Render(const Sprite2D &sprite)
{
    sprite.CalculateModelMatrix();
    
    this->Render(sprite.GetMesh(), *sprite.GetShader());
}

void Renderer::Render(SpriteBatch &batch)
{
    batch.PrepareForRender();

    auto shader = batch.GetShader();
    if(!shader || !shader->IsValid()){
        spdlog::warn("Core::Renderer:Render(const QuadBatch &batch), Warning: Shader is not valid");
    }
    
    shader->UseShader();
    auto texture = batch.GetTexture();
    texture->Bind();

    Uniform::SetShaderUniformInt1(*shader, "u_texture", 0);
    
    auto va = batch.GetVertexArray();
    auto ib = batch.GetIndexBuffer();

    if(!va){
        spdlog::warn("Core::Renderer:Render(const QuadBatch &batch), Warning: VertexArray is nullptr");
        return;
    }

    if(!ib){
        spdlog::warn("Core::Renderer:Render(const QuadBatch &batch), Warning: IndexBuffer is nullptr");
        return;
    }

    size_t matrix_count{batch.GetModelMatrices().size()}, index_count{ib->GetCount()};
    va->Bind();
    batch.UpdateModel();
    ib->Bind();
    glDrawElementsInstanced(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr, matrix_count);
    va->UnBind();

    glActiveTexture(GL_TEXTURE0);
}

void Renderer::SwapBuffers(Window &window)
{
    glfwSwapBuffers(window);
}
