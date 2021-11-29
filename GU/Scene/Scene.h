/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/TimeStep.h"
#include<entt.hpp>
#include<string>
#include<memory>
namespace GU
{
    class Entity;
    class GU_API Scene
    {
    public:
        Scene();
        ~Scene();
        void OnUpdate(TimeStep ts);
        Entity CreateEntity(const std::string& name = std::string());
        entt::registry m_Registry;
    };

    class GU_API Entity
    {
    public:
        Entity() = default;
        Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			return component;
		}

        Entity( const entt::entity& handle, Scene* scene )
            : m_EntityHandle(handle), m_Scene(scene)
        {}
    private:
        entt::entity m_EntityHandle; 
        Scene* m_Scene;
    };
}