/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/Shader.h"
#include"Core/Core.h"
namespace GU
{
    class GU_API OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
        virtual ~OpenGLShader();
        void Bind() override;
        void Unbind() override;
    private:
        void CheckCompileErrors(unsigned int shader, std::string type);
        uint32_t m_RendererID;
        std::string m_Name;
    };
}