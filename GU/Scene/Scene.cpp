/*
 * @Author: ImGili
 * @Description: 
 */
#include"Scene/Scene.h"
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
    return entity;
}

void Scene::OnUpdate(TimeStep ts)
{
    auto view = m_Registry.view<ColorComponet, V2PositionComponet>();
    for (auto entity : view)
    {
        auto color = view.get<ColorComponet>(entity);
        V2PositionComponet position = view.get<V2PositionComponet>(entity);
        Renderer2D::DrawQuad(position.Position, color.Color);
    }
}