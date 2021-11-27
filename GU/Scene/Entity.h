/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/Assert.h"
#include"Scene/Scene.h"
#include<entt.hpp>
namespace GU
{
    class Scene;
    class GU_API Entity
    {
    public:
        Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            GU_ASSERT(!HasComponent<T>(), "Entity already has component!");
            return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
        }
    private:
        entt::entity m_EntityHandle{0};
        Scene* m_Scene = nullptr;
    };
}