/*
 * @Author: ImGili
 * @Description: 
 */
#include"Scene/Scene.h"
#include"Scene/Component.h"
using namespace GU;
Scene::Scene()
{}
Scene::~Scene()
{}

Entity Scene::CreateEntity(const std::string& name)
{
    Entity entity = { m_Registry.create(), this };
    auto& tag = entity.AddComponent<TagComponent>();
    tag.Tag = name.empty() ? "Entity" : name;
    return entity;
}
