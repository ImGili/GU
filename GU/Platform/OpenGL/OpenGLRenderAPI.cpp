/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/OpenGL/OpenGLRenderAPI.h"
#include<glad/glad.h>
using namespace GU;
void OpenGLRenderAPI::Init()
{

}

void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
