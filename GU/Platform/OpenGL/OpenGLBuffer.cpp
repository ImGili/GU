/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/OpenGL/OpenGLBuffer.h"
#include"glad/glad.h"
using namespace GU;
OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(float* data, uint32_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout& bufferLayout)
{
    m_Layout = bufferLayout;
}

const BufferLayout& OpenGLVertexBuffer::GetLayout() const
{
    return m_Layout;
}

//============OpenGLIndexBuffer==========================

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indics, uint32_t count)
    : m_Count(count)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t),indics, GL_STATIC_DRAW);
}

void OpenGLIndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}