/*
 * @Author: ImGili
 * @Description: 
 */
#include"Scene/Scene.h"
#include"Scene/Entity.h"
#include"Scene/Component.h"
#include"Renderer/Renderer2D.h"
using namespace GU;
Scene::Scene()
{
}
Scene::~Scene()
{}

Entity Scene::CreateEntity(const std::string& name)
{
    Entity entity = { m_Registry.create(), this };
    entity.AddComponent<TransformComponent>();
    auto Tag = entity.AddComponent<TagComponent>();
    Tag.Tag = name.empty() ? "Entity" : name;
    return entity;
}

void Scene::OnUpdate(TimeStep ts)
{
    auto view = m_Registry.view<CameraComponent, TransformComponent>();
    for (auto entity : view)
    {
        auto [camera, transform] = view.get<CameraComponent, TransformComponent>(entity);
        Renderer2D::BeginScene(camera.Camera, transform.Transform);
    }
    
    auto group = m_Registry.group<ColorComponet>(entt::get<V2PositionComponet>);
    for (auto entity : group)
    {

        auto [position, color] = group.get<V2PositionComponet, ColorComponet>(entity);
        Renderer2D::DrawQuad(position, color);
    }
    Renderer2D::EndScene();
}