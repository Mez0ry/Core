#ifndef __SHADER_HPP__
#define __SHADER_HPP__
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "Base.hpp"

class Shader
{
private:
    Scope<FragmentShader> m_FragmentShader;
    Scope<VertexShader> m_VertexShader;
    std::uint32_t m_Id;
public:
    Shader(Scope<VertexShader> vertex_shader, Scope<FragmentShader> fragment_shader);
    /**
     * @param shader_path - path to the file which represents fragment and vertex shaders
     */
    Shader(const std::string& shader_path);

    void UseShader() const;
    
    [[nodiscard]] static std::uint32_t CreateProgram();
    void AttachShaders();
    static Shader CreateShader(Scope<VertexShader> vertex_shader, Scope<FragmentShader> fragment_shader);

    void LinkShader();
    static void LinkShader(std::uint32_t id);

    std::uint32_t GetId() const;
    std::uint32_t GetVertexId() const;
    std::uint32_t GetFragmentId() const;

    void Setup();
    /**
     * @brief Deletes vertex and fragment shader
    */
    void Cleanup();
};

#endif //!__SHADER_HPP__