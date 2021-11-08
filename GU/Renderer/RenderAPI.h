#pragma once
#include"Core/Core.h"
namespace GU
{
    class GU_API RenderAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL
        };
        static API GetAPI();
    private:
        static API s_API;
    };
}