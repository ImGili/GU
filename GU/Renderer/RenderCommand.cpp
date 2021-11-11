/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/RenderCommand.h"
#include"Renderer/RenderAPI.h"
using namespace GU;

std::unique_ptr<RenderAPI> RenderCommand::s_RenderAPI = RenderAPI::Create();

void RenderCommand::Init()
{
    s_RenderAPI->Init();
}

void RenderCommand::Clear()
{
    s_RenderAPI->Clear();
}

void RenderCommand::SetClearColor(const glm::vec4& color)
{
    s_RenderAPI->SetClearColor(color);
}

 void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
 {
     s_RenderAPI->DrawIndexed(vertexArray, indexCount);
 }
