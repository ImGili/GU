/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
using namespace GU;
void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexarray, const glm::mat4& transform)
{
    // TODO: transform变换
    shader->Bind();
    vertexarray->Bind();
    RenderCommand::DrawIndexed(vertexarray);
}