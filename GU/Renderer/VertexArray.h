/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/Buffer.h"
#include<memory>
namespace GU
{
    class GU_API VertexArray
    {
    public:
        virtual ~VertexArray() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

        static std::shared_ptr<VertexArray> Create();
    private:
    };
}