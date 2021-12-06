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

        template<typename T>
        bool RemoveComponent()
        {
            GU_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        Entity( const entt::entity& handle, Scene* scene )
            : m_EntityHandle(handle), m_Scene(scene)
        {}

        operator uint32_t() const { return (uint32_t) m_EntityHandle; }
        bool operator==(const Entity& other) const { return other.m_EntityHandle == m_EntityHandle && m_Scene==other.m_Scene; }
        operator bool() const { return m_EntityHandle != entt::null; }
        operator entt::entity() const { return m_EntityHandle; }
    private:
        entt::entity m_EntityHandle{entt::null}; 
        Scene* m_Scene{nullptr};
    };
}