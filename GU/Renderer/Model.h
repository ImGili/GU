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
#include<vector>
namespace GU
{
    // TODO: 单一mesh的模型
    class GU_API Model
    {
    public:
        Model(const std::string& path);

        static std::shared_ptr<Model> Create(const std::string& path);
        const  std::vector<std::shared_ptr<Mesh>>& GetMeshs() const { return m_Meshs;}
    private:
        void ProcessNode(aiNode* node, const aiScene* scene);
        std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::shared_ptr<Texture2D> LoadMaterialTexture(aiMaterial* material, aiTextureType type);
        std::vector<std::shared_ptr<Mesh>> m_Meshs;
        std::string directory;
    };
}