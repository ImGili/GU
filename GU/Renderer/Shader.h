/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include<memory>
#include<string>
#include"Core/Core.h"
namespace GU
{
    class GU_API Shader
    {
    public:
        virtual ~Shader() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        static std::shared_ptr<Shader> Create(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    private:
    };
}