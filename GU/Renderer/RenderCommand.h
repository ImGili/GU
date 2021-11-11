/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/RenderAPI.h"
#include<glm/glm.hpp>
#include<memory>
namespace GU
{
    class GU_API RenderCommand
    {
    public:
        static void Init();
        static void SetClearColor(const glm::vec4& color);
        static void Clear();
    private:
        static std::unique_ptr<RenderAPI> s_RenderAPI;
    };
}