/*
 * @Author: ImGili
 * @Description: 
 */
#include"OpenGLContext.h"
#include"Core/Assert.h"
using namespace GU;
OpenGLContext::OpenGLContext(void* window)
    : m_Window(static_cast<GLFWwindow*>(window))
{
    GU_ASSERT(static_cast<GLFWwindow*>(window), "OpenGLContext window is wrong!");
}
void OpenGLContext::Init()
{

}

void OpenGLContext::SwapBuffers()
{
    
}