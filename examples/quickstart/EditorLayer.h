/*
 * @Author: ImGili
 * @Description: Editor UI 
 */
#pragma once
#include"Core/Layer.h"
#include"Renderer/FrameBuffer.h"
#include"Renderer/Shader.h"
#include"Renderer/VertexArray.h"
#include"Renderer/Buffer.h"
#include"Renderer/Texture.h"
#include"Renderer/OrthographicCameraController.h"
#include"Renderer/EditorCamera.h"
#include"Scene/Scene.h"
#include"Scene/Entity.h"
#include"Events/Event.h"
#include"Events/KeyEvent.h"
#include"Panels/SceneHierarchyPanel.h"
#include"Panels/ContentBrowserPanel.h"
#include<glm/glm.hpp>
#include<string>
#include<entt.hpp>
using namespace GU;

class EditorLayer : public Layer
{
public:
    EditorLayer();
    ~EditorLayer() = default;

    void OnAttach() override;
    void OnUpdate(TimeStep ts) override;
    void OnImGuiRender() override;
    void OnEvent(Event& e) override;
private:
    bool OnKeyPressed(KeyPressedEvent& e);
    bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
    EditorCamera m_EditorCamera;
    std::shared_ptr<FrameBuffer> m_FrameBuffer;
    glm::vec2 m_ViewportBounds[2];
    bool m_ViewportFocused = false, m_ViewportHovered = false;
    glm::vec2 m_ViewportSize = glm::vec2 (0.0f, 0.0f);
    OrthographicCameraController m_OrthographicCameraController;
    bool m_IsViewportFocus = false;
    std::shared_ptr<Scene> m_ActiveScene;
    Entity m_CameraEntity;
    Entity m_SecondCameraEntity;
    Entity m_HoveredEntity;
    SceneHierarchyPanel m_SceneHierarchyPanel;
    ContentBrowserPanel m_ContentBrowserPanel;
    bool OpenScene = false;
    bool SaveScene = false;

    int m_GizmoType = -1;
};
