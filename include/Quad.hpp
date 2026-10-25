#ifndef __QUAD_HPP__
#define __QUAD_HPP__
#include "Base.hpp"
#include <vector>

BASE_FWD_DECLARE_CLASS(Vertex2D);
BASE_FWD_DECLARE_CLASS(BufferLayout);

class Quad{
private:
    static std::vector<Vertex2D> m_Vertices;
    static BufferLayout m_BufferLayout;
    Quad();
    Quad(const size_t amount);
    
    ~Quad() = default;
public:
    static std::vector<Vertex2D> GetVertices();
    static std::vector<uint32_t> GenerateQuadIndices(const uint32_t start_index = 0);

};
#endif //!__QUAD_HPP__