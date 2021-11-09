/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/Shader.h"
namespace GU
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragSrc);
        ~OpenGLShader() = default;

    private:
        uint32_t m_RenderID;
        std::string m_Name;
    };
}