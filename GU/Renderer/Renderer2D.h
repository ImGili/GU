/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"glm/glm.hpp"
#include"Renderer/OrthographicCamera.h"
namespace GU
{
    // TODO: 2D Renderer
    class GU_API Renderer2D
    {
    public:
        static void Init();

        static void BeginScene(const OrthographicCamera& camera);

        static void DrawQuad(const glm::mat4& tranfom);

        static void EndScene();

        static void Flush();
    };
}