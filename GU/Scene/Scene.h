/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/TimeStep.h"
#include"Scene/Entity.h"
#include<entt.hpp>
#include<string>
namespace GU
{
    class Entity;
    class GU_API Scene
    {
    public:
        Scene();
        ~Scene();
        Entity& CreateEntity(const std::string& name = std::string());
        void OnUpdate(TimeStep st);
    private:
        entt::registry m_Registry;

        friend class Entity;
    };
}