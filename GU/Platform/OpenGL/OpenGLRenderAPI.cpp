/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/OpenGL/OpenGLRenderAPI.h"
#include<glad/glad.h>
using namespace GU;
void OpenGLRenderAPI::Init()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
{
    uint32_t count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderAPI::DrawArray(uint32_t count, uint32_t drawFlag)
{
    glDrawArrays(drawFlag, 0, count);
}