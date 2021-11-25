/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/Mesh.h"
#include"Renderer/Texture.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<memory>
#include<string>
namespace GU
{
    // TODO: 单一mesh的模型
    class GU_API Model
    {
    public:
        Model(const std::string& path);

        static std::shared_ptr<Model> Create(const std::string& path);
        const std::shared_ptr<Mesh>& GetMesh() const;
        const std::shared_ptr<Texture2D>& GetTexture() const{ return m_Texture; }

    private:
        std::shared_ptr<Mesh> m_Mesh;
        std::shared_ptr<Texture2D> m_Texture;
    };
}