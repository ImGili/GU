/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/RenderAPI.h"
#include"Core/Core.h"
#include<glad/glad.h>
namespace GU
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void Init() override;
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
        virtual void DrawArray(uint32_t count, uint32_t drawFlag = GL_TRIANGLES) override;
    };
}