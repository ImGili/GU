/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<memory>
#include<vector>
namespace GU
{
    enum class FrameBufferTextureFormat
    {
        None = 0,
        RGBA8,

        DEPTH24STENCIL8,

        Depth = DEPTH24STENCIL8
    };

    struct FrameBufferTextureSpecification
    {
        FrameBufferTextureSpecification() = default;
        FrameBufferTextureSpecification(FrameBufferTextureFormat format)
            :TextureFormat(format)
        {}

        FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
    };

    struct FrameBufferAttachmentSpecification
    {
        FrameBufferAttachmentSpecification() = default;
        FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
            : Attachments(attachments)
        {}

        std::vector<FrameBufferTextureSpecification> Attachments;
    };

    struct FrameBufferSpecification
    {
        uint32_t Width, Height;
        FrameBufferAttachmentSpecification AttachmentsSpecification;
    };
    
    class FrameBuffer
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
        virtual void Resize(uint32_t width, uint32_t height) = 0;
        static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecification& spec);
        virtual const FrameBufferSpecification& GetSpec() const = 0;
    };
}