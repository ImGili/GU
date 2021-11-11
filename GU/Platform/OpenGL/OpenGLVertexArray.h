/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/VertexArray.h"
#include"Renderer/Buffer.h"
#include"Core/Core.h"
#include<vector>
namespace GU
{
    class GU_API OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() override;
        void Unbind() override;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        uint32_t m_VertexBufferIndex = 0;
    };
}