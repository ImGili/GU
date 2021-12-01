/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/Buffer.h"
namespace GU
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const void* data, uint32_t size);
        OpenGLVertexBuffer(uint32_t size);
        virtual ~OpenGLVertexBuffer();
        void Bind() override;
        void Unbind() override;

        void SetLayout(const BufferLayout& bufferLayout) override;
        const BufferLayout& GetLayout() const override;

        void SetData(const void* data, uint32_t size) override;
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer() = default;
        OpenGLIndexBuffer(const uint32_t* indics, uint32_t count);
        ~OpenGLIndexBuffer() = default;
        void Bind() override;
        void Unbind() override;
        uint32_t GetCount() override;
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}