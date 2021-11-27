/*
 * @Author: ImGili
 * @Description: 
 */
#include"Scene/Scene.h"
#include"Scene/Component.h"
#include"Renderer/Renderer2D.h"
using namespace GU;
Scene::Scene()
{}
Scene::~Scene()
{}

Entity& Scene::CreateEntity(const std::string& name)
{
    Entity entity = { m_Registry.create(), this };
    auto& tag = entity.AddComponent<TagComponent>();
    tag.Tag = name.empty() ? "Entity" : name;
    entity.AddComponent<SpriteRendererComponent>();
    return entity;
}

void Scene::OnUpdate(TimeStep st)
{
    auto group = m_Registry.group<V2PositionComponet>(entt::get<ColorComponet>);
    for (auto entity : group)
    {
        auto [ position, color ] = group.get<V2PositionComponet, ColorComponet>(entity);
        Renderer2D::DrawQuad(position.Position, color.Color);
    }
}
