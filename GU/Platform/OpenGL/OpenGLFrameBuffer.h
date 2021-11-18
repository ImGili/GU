/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/FrameBuffer.h"
namespace GU
{
    class GU_API OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification& spec);

        ~OpenGLFrameBuffer();

        void Bind() override;
        void Unbind() override;
        void Resize(uint32_t width, uint32_t height) override;
        uint32_t GetColorAttachmentRendererID() const override;
        const FrameBufferSpecification& GetSpec() const override { return m_Specification;}
    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
        FrameBufferSpecification m_Specification;
        void Invalidate();
    };
}