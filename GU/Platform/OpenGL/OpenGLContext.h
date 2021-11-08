/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/GraphicsContext.h"
#include"Core/Core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace GU
{
    class GU_API OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(void* window);
        virtual void Init() override;
        virtual void SwapBuffers() override;     
    private:
        GLFWwindow* m_Window;
    };
}