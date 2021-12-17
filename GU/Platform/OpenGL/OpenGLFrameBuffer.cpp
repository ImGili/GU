/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/OpenGL/OpenGLFrameBuffer.h"
#include"Core/Assert.h"
#include<glad/glad.h>
#include"Core/Log.h"
namespace GU
{
    namespace Utils
    {
        static bool isDepthFormat(FrameBufferTextureFormat format)
        {
            switch (format)
            {
                case FrameBufferTextureFormat::DEPTH24STENCIL8:
                {
                    return true;
                    break;
                }
            }
            return false;
        }

        static void CreateTextures(uint32_t* outID, uint32_t count)
        {
            glGenTextures(count, outID);
        }
        static void CreateRenderbuffers(uint32_t* outID, uint32_t count)
        {
            glGenRenderbuffers(count, outID);
        }

        static void BindTexture(uint32_t id)
        {
            glBindTexture(GL_TEXTURE_2D, id);
        }
        static void BindRBO(uint32_t id)
        {
            glBindRenderbuffer(GL_RENDERBUFFER, id);
        }
        static void AttachColorTexture(uint32_t id, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, id, 0);
        }
        static void AttachDepthTexture(uint32_t id, GLenum format, uint32_t width, uint32_t height)
        {
            glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, id);
        }
    }
    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec )
        : m_Specification(spec)
    {
        for (auto attach : m_Specification.AttachmentsSpecification.Attachments)
        {
            if (!Utils::isDepthFormat(attach.TextureFormat))
                m_ColorAttachmentSpecifications.emplace_back(attach);
            else
                m_DepthAttachmentSpecification = attach;
        }
        
        Invalidate();
    }

    void OpenGLFrameBuffer::Invalidate()
    {
        if (m_RendererID){
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
            glDeleteRenderbuffers(1, &m_DepthAttachment);
            m_ColorAttachments.clear();
            m_DepthAttachment = 0;
        }

        // 帧缓冲创建
        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        // 帧缓冲纹理创建
        if (m_ColorAttachmentSpecifications.size())
        {
            m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
            Utils::CreateTextures(m_ColorAttachments.data(), m_ColorAttachments.size());
            for (size_t i = 0; i < m_ColorAttachments.size(); i++)
            {
                Utils::BindTexture(m_ColorAttachments[i]);
                switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
					case FrameBufferTextureFormat::RGBA8:
						Utils::AttachColorTexture(m_ColorAttachments[i], GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, i);
						break;
					case FrameBufferTextureFormat::RED_INTEGER:
						Utils::AttachColorTexture(m_ColorAttachments[i], GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
						break;
				}
            }
        }
        if (m_DepthAttachmentSpecification.TextureFormat != FrameBufferTextureFormat::None)
        {
            Utils::CreateRenderbuffers(&m_DepthAttachment, 1);
            Utils::BindRBO(m_DepthAttachment);
            switch (m_DepthAttachmentSpecification.TextureFormat)
            {
            case FrameBufferTextureFormat::DEPTH24STENCIL8:
                {
                    Utils::AttachDepthTexture(m_DepthAttachment, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
                    break;
                }
            }
        }

        if (m_ColorAttachments.size() > 1)
		{
			GU_ASSERT(m_ColorAttachments.size() <= 4,"Framebuffer color size less than 4");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}
        
        // glGenTextures(1, &m_ColorAttachment);
        // glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Specification.Width, m_Specification.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // glBindTexture(GL_TEXTURE_2D, 0);

        // 将它附加到当前绑定的帧缓冲对象
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

        // 创建渲染缓冲对象
        // glGenRenderbuffers(1, &m_DepthAttachment);
        // glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment);
        // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
        // glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment);

        GU_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Specification.Width, m_Specification.Height);
    }
    void OpenGLFrameBuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
        glDeleteRenderbuffers(1, &m_DepthAttachment);
    }

    uint32_t OpenGLFrameBuffer::GetColorAttachmentRendererID(uint32_t index) const
    {
        // GU_ASSERT(index > m_ColorAttachments.size(), "index is over size of colorattach");
        return m_ColorAttachments[index];
    }

    void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
    {
        m_Specification.Width=width;
        m_Specification.Height = height;
        Invalidate();
    }
    int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
    {
        GU_ASSERT(attachmentIndex < m_ColorAttachments.size(), "attachmentIndex is greater than size of attachments");

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
    }
}
