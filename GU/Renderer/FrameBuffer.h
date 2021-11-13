/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<memory>
namespace GU
{
    struct GU_API FrameBufferSpecification
    {
        uint32_t Width, Height;
    };
    
    class GU_API FrameBuffer
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual uint32_t GetColorAttachmentRendererID() const = 0;
        static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecification& spec);
    };
}