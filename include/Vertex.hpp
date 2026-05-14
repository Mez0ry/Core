#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__
#include <glm/glm.hpp>
#include <cstdint>

constexpr int32_t G_MAX_BONE_INFLUENCE = 4;

struct Vertex2D{
    glm::vec2 position; 
    glm::vec3 normal;
    glm::vec2 texture; 

    glm::vec3 tangent;
    glm::vec3 bitangent;

	int32_t bones[G_MAX_BONE_INFLUENCE];
	float weights[G_MAX_BONE_INFLUENCE];

	Vertex2D(glm::vec2 position_, glm::vec3 normal_, glm::vec2 texture_ = glm::vec2());
    Vertex2D(glm::vec2 position_, glm::vec3 normal_, glm::vec2 texture_, glm::vec3 tangent_ , glm::vec3 bitangent_); 
};
#endif //!__VERTEX_HPP__