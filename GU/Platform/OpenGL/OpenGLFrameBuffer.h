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
    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthAttachment;
        FrameBufferSpecification m_Specification;
    };
}