/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/Mesh.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<memory>
namespace GU
{
    // TODO: 单一mesh的模型
    class GU_API Model
    {
    public:
        Model(const char* path);

        static std::shared_ptr<Model> Create(const char* path);

    private:
        std::shared_ptr<Mesh> m_Mesh;
    };
}