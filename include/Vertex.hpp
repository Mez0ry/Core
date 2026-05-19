#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__
#include <glm/glm.hpp>
#include <cstdint>

struct Vertex2D{
    glm::vec2 position; 
    glm::vec3 normal;
    glm::vec2 texture_pos; 

    glm::vec3 tangent;
    glm::vec3 bitangent;

	Vertex2D(glm::vec2 position_, glm::vec3 normal_, glm::vec2 texture_ = glm::vec2());
    Vertex2D(glm::vec2 position_, glm::vec3 normal_, glm::vec2 texture_, glm::vec3 tangent_ , glm::vec3 bitangent_); 
};

#endif //!__VERTEX_HPP__