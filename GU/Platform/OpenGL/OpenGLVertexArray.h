/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/VertexArray.h"

namespace GU
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() override;
        void Unbind() override;

        void SetVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) override;
    private:
        uint32_t m_RendererID;
    };
}