#include "Renderer.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#include "Mesh.hpp"
#include "Uniform.hpp"
#include "Sprite2D.hpp"

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

#include <iostream>

void Renderer::Render(const Mesh &mesh, const Shader &shader, GLenum render_mode, uint32_t data_type)
{
    if(!shader.IsValid()){
        spdlog::warn("Core::Renderer:Render(const Mesh&, const Shader&, GLenum, uint32_t), Warning: Shader is not valid");
    }

    shader.UseShader();
    
    auto& textures = mesh.GetTextures();
    
    unsigned int diffuse_nr = 1;
    unsigned int specular_nr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {        
        std::string uniform_name;
        switch (textures[i].type)
        {
            case TextureType::Diffuse:
                uniform_name = "u_diffuse" + std::to_string(diffuse_nr++);
                break;
            case TextureType::Specular:
                uniform_name = "u_specular" + std::to_string(specular_nr++);
                break;
            case TextureType::Base:
                uniform_name = textures[i].str_type; 
                break;
            default:
                uniform_name = textures[i].str_type;
        }

        textures[i].texture->Bind(i);
        Uniform::SetShaderUniformInt1(shader, uniform_name, i);
    }

    auto& va = mesh.GetVertexArray();
    auto& ib = mesh.GetIndexBuffer();
    va->Bind();
    ib->Bind();
    
    glDrawElements(render_mode, ib->GetCount(), data_type, nullptr);
    va->UnBind();

    glActiveTexture(GL_TEXTURE0);
}

void Renderer::Render(const Sprite2D &sprite)
{
    sprite.Update();
    this->Render(sprite.GetMesh(), *sprite.GetShader());
}

void Renderer::SwapBuffers(Window &window)
{
    glfwSwapBuffers(window);
}
