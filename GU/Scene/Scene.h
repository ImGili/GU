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
    class Scene
    {
    public:
        Scene();
        ~Scene();
        void OnUpdate(TimeStep ts);
        Entity CreateEntity(const std::string& name = std::string());
    private:
        entt::registry m_Registry;

    private:
        friend class Entity;
    };
}