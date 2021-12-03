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
    Camera* mainCamera = nullptr;
    glm::mat4 cameraTransform;
    {
        auto view = m_Registry.view<TransformComponent, CameraComponent>();
        for (auto entity : view)
        {
            auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
            
            if (camera.Primary)
            {
                mainCamera = &camera.Camera;
                cameraTransform = transform.Transform;
                break;
            }
        }
    }

    if (mainCamera)
    {
        Renderer2D::BeginScene(*mainCamera, cameraTransform);

        auto group = m_Registry.group<ColorComponet>(entt::get<V2PositionComponet>);
        for (auto entity : group)
        {

            auto [position, color] = group.get<V2PositionComponet, ColorComponet>(entity);
            Renderer2D::DrawQuad(position, color);
        }

        Renderer2D::EndScene();
    }
    
}

void Scene::OnViewportResize(uint32_t width, uint32_t height)
{
    m_ViewportWidth = width;
    m_ViewportHeight = height;

    // Resize our non-FixedAspectRatio cameras
    auto view = m_Registry.view<CameraComponent>();
    for (auto entity : view)
    {
        auto& cameraComponent = view.get<CameraComponent>(entity);
        cameraComponent.Camera.SetViewportSize(width, height);
    }

}