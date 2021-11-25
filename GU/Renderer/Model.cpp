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
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        GU_ERROR("Assimp scene Error");
    }
    aiMesh* mesh = scene->mMeshes[0];
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
    m_Mesh = Mesh::Create(meshVertexs, meshIndics);

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    aiString str;
    material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
    std::string directory = path.substr(0, path.find_last_of('/'));
    std::string filename = directory + '/' + str.data;
    if (str.length>0)
    {
        m_Texture = Texture2D::Create(filename);
    }
}


std::shared_ptr<Model> Model::Create(const std::string& path)
{
    return std::make_shared<Model>(path);
}

const std::shared_ptr<Mesh>& Model::GetMesh() const
{
    return m_Mesh;
}