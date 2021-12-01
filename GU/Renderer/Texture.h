/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<string>
#include<memory>
namespace GU
{
    class Texture
    {
    public:
        virtual ~Texture() = default;
        virtual void Bind(uint32_t slot) = 0;
        virtual void SetData(void* data, uint32_t size) = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height);
        static std::shared_ptr<Texture2D> Create(const std::string& path);
    };
}