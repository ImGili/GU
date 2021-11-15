/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
#include"Renderer/Renderer2D.h"
using namespace GU;
void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexarray, const glm::mat4& transform)
{
    // TODO: transform变换
    shader->Bind();
    vertexarray->Bind();
    RenderCommand::DrawIndexed(vertexarray);
}

void Renderer::Init()
{
    Renderer2D::Init();
}