#pragma once
#include"Core/Core.h"
#include"glm/glm.hpp"
#include"Renderer/VertexArray.h"
#include<glad/glad.h>
#include<memory>
namespace GU
{
    class RenderAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL
        };
        static API GetAPI();
        static std::unique_ptr<RenderAPI> Create();
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Init() = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
        virtual void DrawArray(uint32_t count, uint32_t drawFlag = GL_TRIANGLES) = 0;
    private:
        static API s_API;
    };
}