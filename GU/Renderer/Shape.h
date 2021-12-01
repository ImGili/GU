/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/VertexArray.h"
#include"Renderer/Buffer.h"
#include"Renderer/Shader.h"
namespace GU
{
    // TODO: implement Line shape class
    class Line
    {
    public:
        Line();
        void Draw();
        std::shared_ptr<VertexBuffer> GetVertexBuffer() { return m_VertexBuffer; }
    private:
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<Shader> m_Shader;
        uint32_t m_Count;
    };
}