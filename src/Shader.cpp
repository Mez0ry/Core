#include "Shader.hpp"
#include "glad/gl.h"
#include <limits>
#include <iostream>
#include <FileReader.hpp>

Shader::Shader(Scope<VertexShader> vertex_shader, Scope<FragmentShader> fragment_shader) : m_VertexShader(std::move(vertex_shader)), m_FragmentShader(std::move(fragment_shader))
{
    Setup();
}

Shader::Shader(const std::string &shader_path)
{
    auto file_content = FileReader::ReadFile(shader_path);
    
    auto vertex_pos = file_content.find("Vertex");
    auto fragment_pos = file_content.find("Fragment");

    auto after_vertex_pos = file_content.find_first_of('\n', vertex_pos) + 1;
    auto before_fragment_pos = file_content.rfind('\n', fragment_pos);

    m_VertexShader = MakeScope<VertexShader>(file_content.substr(after_vertex_pos, before_fragment_pos - after_vertex_pos).c_str());
    m_FragmentShader = MakeScope<FragmentShader>(file_content.substr(file_content.find_first_of('\n', fragment_pos)).c_str());
    Setup();
}

void Shader::UseShader() const{
    glUseProgram(m_Id);
}

std::uint32_t Shader::CreateProgram() { return glCreateProgram(); }

void Shader::AttachShaders() {
    glAttachShader(m_Id, m_VertexShader->GetId());
    glAttachShader(m_Id, m_FragmentShader->GetId());
}

Shader Shader::CreateShader(Scope<VertexShader> vertex_shader, Scope<FragmentShader> fragment_shader)
{
    Shader shader(std::move(vertex_shader), std::move(fragment_shader));

    return shader;
}

void Shader::LinkShader() {
    LinkShader(m_Id);
}

void Shader::LinkShader(std::uint32_t id) {
    glLinkProgram(id);
    int  success;
    char info_log[512];

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, info_log);
        std::cout << "Shader::LinkShader, status: LINKING_FAILED, " << info_log << '\n';
    }
}

std::uint32_t Shader::GetId() const
{
    return m_Id;
}

std::uint32_t Shader::GetVertexId() const
{
    return m_VertexShader->GetId();
}

std::uint32_t Shader::GetFragmentId() const
{
    return m_FragmentShader->GetId();
}

void Shader::Setup() {
    if(m_Id){
        //handle
    }
    m_Id = CreateProgram();
    AttachShaders();
    LinkShader();
    Cleanup();
}

void Shader::Cleanup() {
    m_FragmentShader->DeleteShader();
    m_VertexShader->DeleteShader();
}
