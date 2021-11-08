/*
 * @Author: ImGili
 * @Description: 
 */
#include"RenderAPI.h"

using namespace GU;

RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

RenderAPI::API RenderAPI::GetAPI()
{
    return s_API;
}
