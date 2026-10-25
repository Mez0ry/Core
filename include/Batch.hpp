#ifndef __BATCH_HPP__
#define __BATCH_HPP__
#include "Vertex.hpp"
#include "Base.hpp"

#include <vector>

BASE_FWD_DECLARE_CLASS(Shader);
BASE_FWD_DECLARE_CLASS(Texture);
BASE_FWD_DECLARE_CLASS(VertexBuffer);
BASE_FWD_DECLARE_CLASS(IndexBuffer);
BASE_FWD_DECLARE_CLASS(BufferLayout);
BASE_FWD_DECLARE_CLASS(VertexArray);
BASE_FWD_DECLARE_CLASS(Sprite2D);

struct BatchConfig{
    uint32_t render_mode;
    uint32_t data_type;
};

class Batch
{
protected:
    Scope<BufferLayout> m_BufferLayout;
    Ref<VertexBuffer> m_VertexBuffer;
    Ref<VertexArray> m_VertexArray;
    Ref<IndexBuffer> m_IndexBuffer;
    std::vector<uint32_t> m_Indicies;
    std::vector<Vertex2D> m_Vertices;
    size_t m_MaxVertices;
    size_t m_UsedVertices{0};
public:
    Batch(const size_t max_vertices);
    
    virtual void PrepareForRender();

    void Add(const Vertex2D &vertex);
    void Add(const std::vector<Vertex2D> &vertices);

    [[nodiscard]] Ref<VertexArray>  GetVertexArray() const;
    [[nodiscard]] Ref<IndexBuffer>  GetIndexBuffer() const;
    const std::vector<Vertex2D>& GetVertices() const;
};

class QuadBatch : public Batch{
protected:
    Ref<Texture> m_Texture;
    Ref<Shader> m_Shader;
public:
    QuadBatch(const size_t max_vertices, const Ref<Texture> texture, const Ref<Shader> shader);

    [[nodiscard]] const Ref<Shader> GetShader() const;
    [[nodiscard]] Ref<Texture> GetTexture() const;
private:
};

class SpriteBatch : public QuadBatch{
private:
    std::vector<Ref<Sprite2D>> m_Sprites;
    Ref<VertexBuffer> m_MatBuffer = {nullptr};
public:
    SpriteBatch(const size_t max_vertices, const Ref<Texture> texture, const Ref<Shader> shader);

    virtual void PrepareForRender() override;

    void AllocInstanceBuffer();
    void UpdateModel();

    void Add(const Ref<Sprite2D> sprite);

    [[nodiscard]] const Ref<Shader> GetShader() const;
    [[nodiscard]] const Ref<Texture> GetTexture() const;

    [[nodiscard]] const std::vector<Ref<Sprite2D>>& GetSprites() const;

    std::vector<glm::mat4> GetModelMatrices() const;
private:
};
#endif //!__BATCH_HPP__