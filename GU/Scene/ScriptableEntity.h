/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Scene/Scene.h"
#include"Core/TimeStep.h"
#include"Entity.h"
namespace GU
{
    class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() {}

        template<typename T>
        T& GetComponent()
        {
            return m_Entity.GetComponent<T>();
        }

        virtual void OnCreate() {}
        virtual void OnUpdate(TimeStep ts) {}
        virtual void OnDestroy() {}
    private:
        Entity m_Entity;
        friend class Scene;
    };
}