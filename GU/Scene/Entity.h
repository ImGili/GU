/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<entt.hpp>
#include"Scene/Scene.h"
namespace GU
{
    class Entity
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