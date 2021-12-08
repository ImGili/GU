/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Scene/Scene.h"
#include"Scene/Entity.h"
#include<memory>
namespace GU
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const std::shared_ptr<Scene>& context){ SetContext(context); }

        ~SceneHierarchyPanel() = default;

        
        void SetContext(const std::shared_ptr<Scene>& context) { m_Context = context;m_SelectionEntity = {}; }

        void OnImGuiRender();

    private:
        /**
         * @brief Draw entity tree
         * 
         * @param entity 
         */
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
        std::shared_ptr<Scene> m_Context;
        Entity m_SelectionEntity;
    };
}
