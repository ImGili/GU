/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"glm/glm.hpp"
namespace GU
{
    // TODO: 2D Renderer
    class GU_API Renderer2D
    {
    public:
        static void Init();

        static void BeginScene();

        static void DrawQuad(const glm::mat4& tranfom);

        static void EndScene();

        static void Flush();
    };
}