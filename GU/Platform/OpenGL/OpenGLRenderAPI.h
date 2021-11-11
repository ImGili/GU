/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/RenderAPI.h"
namespace GU
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void Init() override;
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
    };
}