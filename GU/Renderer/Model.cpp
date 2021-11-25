/*
 * @Author: ImGili
 * @Description: 
 */
#include"Core/Log.h"
#include"Core/Assert.h"
#include"Renderer/Model.h"
#include"Renderer/Mesh.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
using namespace GU;
Model::Model(const std::string& path)
{
    directory = path.substr(0, path.find_last_of('/'));
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        GU_ERROR("Assimp scene Error");
    }
    ProcessNode(scene->mRootNode, scene);
}


std::shared_ptr<Model> Model::Create(const std::string& path)
{
    return std::make_shared<Model>(path);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshs.push_back(ProcessMesh(mesh, scene));
    }

    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}
std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<MeshVertex> meshVertexs;
    std::vector<uint32_t> meshIndics;
    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        GU_ASSERT(mesh->mTextureCoords[0], "Mesh hasn't TexCoord!");
        meshVertexs.push_back({
            {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
            {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y}
            });
    }
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            meshIndics.push_back(face.mIndices[j]);
        }
    }
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    return Mesh::Create(meshVertexs, meshIndics, LoadMaterialTexture(material, aiTextureType_DIFFUSE));
}

std::shared_ptr<Texture2D> Model::LoadMaterialTexture(aiMaterial* material, aiTextureType type)
{
    aiString str;
    material->GetTexture(type, 0, &str);
    GU_ASSERT(str.length>0, "Model must have texture img!");
    std::string filename = directory + '/' + str.data;
    return Texture2D::Create(filename);
}
