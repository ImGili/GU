/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"glm/glm.hpp"
#include"Renderer/OrthographicCamera.h"
#include"Renderer/EditorCamera.h"
#include"Renderer/Camera.h"
namespace GU
{
    // TODO: 2D Renderer
    class Renderer2D
    {
    public:
        static void Init();

        static void BeginScene(const OrthographicCamera& camera);
        static void BeginScene(const EditorCamera& camera);
        static void BeginScene(const Camera& camera, const glm::mat4& transform);

        static void DrawQuad(const glm::vec2& position, const glm::vec4& color = {1.0f, 0.5f, 0.2f, 1.0f});
        static void DrawQuad(const glm::vec2& position, const glm::vec2 size, const glm::vec4& color = {1.0f, 0.5f, 0.2f, 1.0f});
        static void DrawQuad(const glm::mat4& tranfom, const glm::vec4& color = {1.0f, 0.5f, 0.2f, 1.0f});

        static void EndScene();

        static void Flush();
    };
}