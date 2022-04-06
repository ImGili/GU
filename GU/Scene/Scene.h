/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/TimeStep.h"
#include"Renderer/EditorCamera.h"
#include<entt.hpp>
#include<string>
#include<memory>
namespace GU
{
    class Entity;
    class Scene
    {
    public:
        Scene();
        ~Scene();
        void OnUpdateRuntime(TimeStep ts);
        void OnUpdateEditor(TimeStep ts, EditorCamera& camera);
        Entity CreateEntity(const std::string& name = std::string());
        void DeleteEntity(Entity entity);
        void OnViewportResize(uint32_t width, uint32_t height);

        Entity GetPrimaryCameraEntity();
    private:
        template<typename T>
        void OnComponentAdd(Entity entity, T component);
    private:
        entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

    private:
        friend class Entity;
		friend class SceneHierarchyPanel;
        friend class SceneSerializer;
    };
}