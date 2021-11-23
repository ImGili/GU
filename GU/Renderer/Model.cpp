/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Model.h"
#include"Renderer/Mesh.h"
using namespace GU;
Model::Model(const char* path)
{

}


std::shared_ptr<Model> Model::Create(const char* path)
{
    return std::make_shared<Model>(path);
}