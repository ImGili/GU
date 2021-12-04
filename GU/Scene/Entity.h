/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/Assert.h"
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
            GU_ASSERT(!HasComponent<T>()," Entity has the component");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			return component;
		}

        template<typename T>
        T& GetComponent()
        {
            GU_ASSERT(HasComponent<T>(), "Entity doesn't has component");
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
        }

        Entity( const entt::entity& handle, Scene* scene )
            : m_EntityHandle(handle), m_Scene(scene)
        {}
    private:
        entt::entity m_EntityHandle; 
        Scene* m_Scene;
    };
}