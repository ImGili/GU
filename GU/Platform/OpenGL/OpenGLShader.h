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
        OpenGLShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
        ~OpenGLShader() = default;
        void Bind() override;
        void Unbind() override;
    private:
        void CheckCompileErrors(unsigned int shader, std::string type);
        uint32_t m_RenderID;
        std::string m_Name;
    };
}