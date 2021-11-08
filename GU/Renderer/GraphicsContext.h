/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<memory>
namespace GU
{
    class GU_API GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
        static std::unique_ptr<GraphicsContext> Create(void* window);
    };
}