#include"SceneHierarchyPanel.h"
#include"Scene/Component.h"
#include<imgui.h>
#include<string>
using namespace GU;

void SceneHierarchyPanel::OnImGuiRender()
{
    ImGui::Begin("Scene Hierarchy");
    m_Context->m_Registry.each(
        [&](auto entityID){
            Entity entity = { entityID, m_Context.get()};
            DrawEntityNode(entity);
        }
    );
    ImGui::End();
}

void SceneHierarchyPanel::DrawEntityNode(Entity entity)
{
    auto& tag = entity.GetComponent<TagComponent>().Tag;
    ImGuiTreeNodeFlags flags = ((m_SelectionEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    bool opended = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity,flags, tag.c_str());
    if (ImGui::IsItemClicked())
    {
        m_SelectionEntity = entity;
    }
    if (opended)
    {
        ImGui::TreePop();
    }
    
}
