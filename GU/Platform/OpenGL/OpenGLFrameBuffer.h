/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/FrameBuffer.h"
namespace GU
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification& spec);

        ~OpenGLFrameBuffer();

        void Bind() override;
        void Unbind() override;
        void Resize(uint32_t width, uint32_t height) override;
        uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override;
        virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;
        const FrameBufferSpecification& GetSpec() const override { return m_Specification;}
    private:
        uint32_t m_RendererID = 0;
        FrameBufferSpecification m_Specification;
        void Invalidate();

        std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecifications;
		FrameBufferTextureSpecification m_DepthAttachmentSpecification = FrameBufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
    };
}