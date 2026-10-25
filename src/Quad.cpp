#include "Quad.hpp"
#include "Vertex.hpp"
#include "BufferLayout.hpp"

std::vector<Vertex2D> Quad::m_Vertices = {
        Vertex2D(glm::vec2(-0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)),
        Vertex2D(glm::vec2(0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.0f, 0.0f)),
        Vertex2D(glm::vec2(0.5f, 0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(1.0f, 1.0f)),
        Vertex2D(glm::vec2(-0.5f, 0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.0f, 1.0f))
    };

BufferLayout Quad::m_BufferLayout = BufferLayout::CreateLayout<Vertex2D>();

Quad::Quad() {

}

Quad::Quad(const size_t amount) {
    
}

std::vector<Vertex2D> Quad::GetVertices() { 
    return m_Vertices; 
}

std::vector<uint32_t> Quad::GenerateQuadIndices(const uint32_t start_index)
{
    const std::vector<uint32_t> quad_indices = {
        start_index, start_index + 1, start_index + 2,
        start_index + 2, start_index + 3, start_index
    };
    return quad_indices;
}
