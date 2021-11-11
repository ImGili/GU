/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/OpenGL/OpenGLVertexArray.h"
#include<glad/glad.h>
using namespace GU;
void OpenGLVertexArray::Bind()
{
    glBindVertexArray(m_RendererID);
}
void OpenGLVertexArray::Unbind()
{
    glBindVertexArray(0);
}
OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}
OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}
void OpenGLVertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer)
{
    // TODO: Set VertexBuffer
}