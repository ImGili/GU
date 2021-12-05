#include"SceneHierarchyPanel.h"
#include"Scene/Component.h"
#include<imgui.h>
#include<string>
#include<glm/gtc/type_ptr.hpp>
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

    ImGui::Begin("Properties");
    if (m_SelectionEntity)
    {
        DrawComponents(m_SelectionEntity);
    }
    
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


void SceneHierarchyPanel::DrawComponents(Entity entity)
{
    auto& tag = entity.GetComponent<TagComponent>().Tag;
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    std::strcpy(buffer, tag.c_str());
    if(ImGui::InputText("Tag", buffer, sizeof(buffer)))
    {
        tag = std::string(buffer);
    }
    if (entity.HasComponent<TransformComponent>())
    {
        auto& transform = entity.GetComponent<TransformComponent>().Translation;
        ImGui::DragFloat3("transform", glm::value_ptr(transform), 0.1f);
    }
    
}
