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

        static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragSrc);

    private:
    };
}