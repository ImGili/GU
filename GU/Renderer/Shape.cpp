/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Shape.h"
#include"Renderer/RenderCommand.h"
using namespace GU;

Line::Line()
    : m_Count(2)
{
}

void Line::Draw()
{
    m_VertexArray->Bind();
    m_Shader->Bind();
    RenderCommand::DrawArray(m_Count, GL_LINES);
}