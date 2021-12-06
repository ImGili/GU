/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include<memory>
#include<string>
#include"Core/Core.h"
#include<glm/glm.hpp>
namespace GU
{
    class Shader
    {
    public:
        virtual ~Shader() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        static std::shared_ptr<Shader> Create(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
        virtual void SetMat4(const std::string &name, const glm::mat4& value) const = 0;
        virtual void SetInt(const std::string &name, uint32_t value) const = 0;
    private:
    };
}