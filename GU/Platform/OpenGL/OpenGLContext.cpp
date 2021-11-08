/*
 * @Author: ImGili
 * @Description: 
 */
#include"OpenGLContext.h"
#include"Core/Assert.h"
#include"Core/Log.h"
using namespace GU;
OpenGLContext::OpenGLContext(GLFWwindow* window)
    : m_Window(window)
{
    GU_ASSERT(window, "OpenGLContext window is wrong!")
}
void OpenGLContext::Init()
{
    GU_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Glad failed to init!");
    GU_INFO("OpenGL Info:");
    GU_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    GU_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    GU_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers()
{
    
}