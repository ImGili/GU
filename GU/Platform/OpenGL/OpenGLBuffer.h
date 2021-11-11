/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/Buffer.h"
namespace GU
{
    class GU_API OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* data, uint32_t size);
        virtual ~OpenGLVertexBuffer();
        void Bind() override;
        void Unbind() override;

        void SetLayout(const BufferLayout& bufferLayout) override;
        const BufferLayout& GetLayout() const override;

        void SetData(float* data, uint32_t size) override;
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class GU_API OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer() = default;
        OpenGLIndexBuffer(uint32_t* indics, uint32_t count);
        ~OpenGLIndexBuffer() = default;
        void Bind() override;
        void Unbind() override;
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}