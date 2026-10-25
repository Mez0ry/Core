#include "Batch.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"
#include "BufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Quad.hpp"
#include "Sprite2D.hpp"

Batch::Batch(const size_t max_vertices) : m_MaxVertices(max_vertices){
  const size_t reserve_size = sizeof(Vertex2D) * m_MaxVertices;
  m_Vertices.reserve(reserve_size);
  m_Indicies.reserve((max_vertices / 4) * 6);
}

void Batch::Add(const Vertex2D &vertex) {
  m_Vertices.push_back(vertex);
}

void Batch::Add(const std::vector<Vertex2D> &vertices)
{
  m_Vertices.insert(m_Vertices.end(), vertices.cbegin(), vertices.cend());

  const uint32_t start_index = (m_Vertices.size() - vertices.size());
  auto indices  = Quad::GenerateQuadIndices(start_index);

  m_Indicies.insert(m_Indicies.end(), indices.begin(), indices.end());
}

Ref<VertexArray> Batch::GetVertexArray() const
{
    return m_VertexArray;
}

Ref<IndexBuffer> Batch::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

const std::vector<Vertex2D>& Batch::GetVertices() const
{
  return m_Vertices;
}

void Batch::PrepareForRender(){
  if(m_IndexBuffer && m_VertexArray){
    return;
  }

  BufferLayout vb_layout;
  vb_layout.Push<Vertex2D>(false);


  m_IndexBuffer = MakeReference<IndexBuffer>(m_Indicies.data(), m_Indicies.size());
  m_VertexArray = MakeReference<VertexArray>(MakeReference<VertexBuffer>(m_Vertices), vb_layout);
}

QuadBatch::QuadBatch(const size_t max_vertices, const Ref<Texture> texture, const Ref<Shader> shader) : Batch(max_vertices), m_Texture(texture), m_Shader(shader) {
  
}

const Ref<Shader> QuadBatch::GetShader() const
{
  return m_Shader;
}

Ref<Texture> QuadBatch::GetTexture() const
{
  return m_Texture;
}

SpriteBatch::SpriteBatch(const size_t max_vertices, const Ref<Texture> texture, const Ref<Shader> shader) : QuadBatch(max_vertices, texture, shader)
{
  QuadBatch::Add(Quad::GetVertices());
}

void SpriteBatch::PrepareForRender(){
  if(m_IndexBuffer && m_VertexArray){
    return;
  }

  QuadBatch::PrepareForRender();

  BufferLayout instance_buffer_layout;
  instance_buffer_layout.Push<glm::mat4>(false);
  m_MatBuffer = MakeReference<VertexBuffer>(GetModelMatrices());
  m_VertexArray->AddBuffer(*m_MatBuffer, instance_buffer_layout);
}

void SpriteBatch::Add(const Ref<Sprite2D> sprite) {
  if (!sprite)
    return;

  m_Sprites.push_back(sprite);
}

void SpriteBatch::UpdateModel()
{ 
  m_VertexArray->Bind();
  m_MatBuffer->Bind();

  const auto matrices = GetModelMatrices();

  glBufferData(
    GL_ARRAY_BUFFER,
    static_cast<GLsizeiptr>(matrices.size() * sizeof(glm::mat4)),
    matrices.empty() ? nullptr : matrices.data(),
    GL_DYNAMIC_DRAW);
}

const Ref<Shader> SpriteBatch::GetShader() const
{
  return m_Shader;
}

const Ref<Texture> SpriteBatch::GetTexture() const
{
  return m_Texture;
}

const std::vector<Ref<Sprite2D>> &SpriteBatch::GetSprites() const {
  return m_Sprites;
}

std::vector<glm::mat4> SpriteBatch::GetModelMatrices() const
{
  std::vector<glm::mat4> matrices;

  for(const auto sprite : m_Sprites) {
    sprite->CalculateModelMatrix();
    matrices.push_back(sprite->GetModel());
  }

  return matrices;
}
