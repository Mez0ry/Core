#include "Vertex.hpp"

Vertex2D::Vertex2D(glm::vec2 position_, glm::vec3 normal_, glm::vec2 texture_) : position( position_), normal(normal_), texture_pos(texture_){

}

Vertex2D::Vertex2D(glm::vec2 position_, glm::vec3 normal_, glm::vec2 texture_, glm::vec3 tangent_, glm::vec3 bitangent_) 
: position( position_), normal(normal_), texture_pos(texture_), tangent(tangent_), bitangent(bitangent_) {

}
