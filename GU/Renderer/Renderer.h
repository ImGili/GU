/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/Shader.h"
#include"Renderer/VertexArray.h"
#include<glm/glm.hpp>
#include<memory>
namespace GU
{
    class Renderer
    {
    public:
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexarray, const glm::mat4& transform = glm::mat4(1));
        static void Init();
    };
}
