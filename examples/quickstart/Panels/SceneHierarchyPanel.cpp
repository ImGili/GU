#include"SceneHierarchyPanel.h"
#include"Scene/Component.h"
#include<imgui.h>
#include<string>
#include<glm/gtc/type_ptr.hpp>
#include<imgui_internal.h>
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

    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionEntity = {};
    
    if (ImGui::BeginPopupContextWindow(0, 1, false))
    {
        if (ImGui::MenuItem("Create Entity"))
        {
            m_Context->CreateEntity("Empty Entity");
        }
        ImGui::EndPopup();
    }

    ImGui::End();

    

    ImGui::Begin("Properties");
    if (m_SelectionEntity)
    {
        DrawComponents(m_SelectionEntity);

        if(ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");
        if(ImGui::BeginPopup("AddComponent"))
        {
            if (ImGui::MenuItem("Add Camera"))
            {
                if (!m_SelectionEntity.HasComponent<CameraComponent>())
                {
                    m_SelectionEntity.AddComponent<CameraComponent>();
                }
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::MenuItem("Add Sprite"))
            {
                if (!m_SelectionEntity.HasComponent<SpriteRendererComponent>())
                {
                    m_SelectionEntity.AddComponent<SpriteRendererComponent>();
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
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
    bool IsDeleteEntity = false;
    if (ImGui::BeginPopupContextItem())
    {
        if(ImGui::MenuItem("Delete Entity"))
            IsDeleteEntity = true;
        ImGui::EndPopup();
    }
    

    if (opended)
    {
        ImGui::TreePop();
    }
    if (IsDeleteEntity)
    {
        m_Context->DeleteEntity(entity);
        if (m_SelectionEntity == entity)
            m_SelectionEntity = {};        
    }
}
static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
{
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    if (ImGui::Button("X", buttonSize))
        values.x = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    if (ImGui::Button("Y", buttonSize))
        values.y = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    if (ImGui::Button("Z", buttonSize))
        values.z = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);
    ImGui::PopID();
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
    const ImGuiTreeNodeFlags treenodeflags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;
    if (entity.HasComponent<TransformComponent>())
    {
        if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), treenodeflags, "Transform"))
        {
            auto& transform = entity.GetComponent<TransformComponent>();
            DrawVec3Control("Translation", transform.Translation);
            DrawVec3Control("Scale", transform.Scale);
            DrawVec3Control("Rotation", transform.Rotation);
            ImGui::TreePop();
        }
    }
    if (entity.HasComponent<CameraComponent>())
    {
        auto& cc = entity.GetComponent<CameraComponent>();
        SceneCamera& camera = cc.Camera;
        float orthoSize = camera.GetOrthographicSize();
        float orthoNearClip = camera.GetOrthographicNearClip();
        float orthoFarClip = camera.GetOrthographicFarClip();
        ImGui::DragFloat("OrthoSize", &orthoSize, 0.1f, 0.0, 20.0);
        ImGui::DragFloat("orthoNearClip", &orthoNearClip, 0.1f, 0.0, 20.0);
        ImGui::DragFloat("orthoFarClip", &orthoFarClip, 0.1f, 0.0, 20.0);
        ImGui::Checkbox("Primary", &cc.Primary);
        camera.SetOrthographicSize(orthoSize);
        camera.SetOrthographicNearClip(orthoNearClip);
        camera.SetOrthographicFarClip(orthoFarClip);
    }

    if (entity.HasComponent<SpriteRendererComponent>())
    {
        auto& spt = entity.GetComponent<SpriteRendererComponent>();
        ImGui::ColorEdit4("Color", glm::value_ptr(spt.Color));
    }
    
    
    
}
