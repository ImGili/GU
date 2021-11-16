/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/OpenGL/OpenGLUniformBuffer.h"
#include"glad/glad.h"
using namespace GU;
OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
    glBufferData(GL_UNIFORM_BUFFER, 152, NULL, GL_DYNAMIC_DRAW); // 分配152字节的内存
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data); 
}

void OpenGLUniformBuffer::Bind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
}
void OpenGLUniformBuffer::Unbind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

OpenGLUniformBuffer::~OpenGLUniformBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}