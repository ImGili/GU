/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<memory>
namespace GU
{
    class GU_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetData(float* data, uint32_t size) = 0;

        static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size);
    };
}
