/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/OpenGL/OpenGLVertexArray.h"
#include<glad/glad.h>
#include"Renderer/Buffer.h"
#include"Core/Assert.h"
using namespace GU;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::None:     break;
        case ShaderDataType::Float:    return GL_FLOAT;
        case ShaderDataType::Float2:   return GL_FLOAT;
        case ShaderDataType::Float3:   return GL_FLOAT;
        case ShaderDataType::Float4:   return GL_FLOAT;
        case ShaderDataType::Mat3:     return GL_FLOAT;
        case ShaderDataType::Mat4:     return GL_FLOAT;
        case ShaderDataType::Int:      return GL_INT;
        case ShaderDataType::Int2:     return GL_INT;
        case ShaderDataType::Int3:     return GL_INT;
        case ShaderDataType::Int4:     return GL_INT;
        case ShaderDataType::Bool:     return GL_BOOL;
    }

    GU_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

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
void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    // TODO: Add VertexBuffer
    GU_ASSERT(vertexBuffer->GetLayout().GetElements().size()>0, "VertexBuffer has no elements, set bufferelement!");
    BufferLayout layout = vertexBuffer->GetLayout();
    Bind();
    vertexBuffer->Bind();
    for (const auto& element : layout)
    {
        switch (element.Type)
        {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        {
            glad_glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset);
            m_VertexBufferIndex++;
            break;
        }
        default:
            break;
        }
    }
    
    Unbind();
    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
}

const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
{
    return m_IndexBuffer;
}