/*
 * @Author: ImGili
 * @Description: 
 */
#include "EditorLayer.h"
#include "Core/Application.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/RenderCommand.h"
#include "ImGui/ImGuiAppConsole.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include"Scene/Component.h"
#include <imgui.h>
#include <cmath>
#include "GLFW/glfw3.h"
EditorLayer::EditorLayer()
    : Layer("EditorLayer"), m_OrthographicCameraController(1280 / 720.0f)
{
}

void EditorLayer::OnUpdate(TimeStep ts)
{
    if (m_IsViewportFocus)
    {
        m_OrthographicCameraController.OnUpdate(ts);
    }

    if (m_ViewportSize.x != 0 && m_ViewportSize.y != 0 && m_FrameBuffer->GetSpec().Width != m_ViewportSize.x || m_FrameBuffer->GetSpec().Height != m_ViewportSize.y)
    {
        m_OrthographicCameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
    }
    m_FrameBuffer->Bind();
    RenderCommand::Clear();
    Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());
    m_ActiveScene->OnUpdate(ts);
    // Renderer2D::DrawQuad(glm::vec2(0.0, 0.0), glm::vec4(1.0, 1.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(-5.0, 5.0), glm::vec4(1.0, 1.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(5.0, 5.0), glm::vec4(0.0, 1.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(-5.0, -5.0), glm::vec4(1.0, 0.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(5.0, -5.0), glm::vec4(1.0, 1.0, 0.0, 1.0));
    Renderer2D::EndScene();
    m_FrameBuffer->Unbind();
}

void EditorLayer::OnImGuiRender()
{

    static bool p_open = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                Application::Get()->Close();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::Begin("Editor");
    ImGui::Button("aaa");
    ImGui::End();

    //=============viewport======================================
    ImGui::Begin("Viewport");
    m_IsViewportFocus = ImGui::IsWindowFocused();
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    m_ViewportSize = glm::vec2(viewportPanelSize.x, viewportPanelSize.y);
    uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
    ImGui::Image(reinterpret_cast<void *>(textureID), ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::End();
    ImGui::End();
}
void EditorLayer::OnAttach()
{
    // Application::Get()->GetWindow().MaxWindow();
    m_ActiveScene = std::make_shared<Scene>();
    auto entity = m_ActiveScene->CreateEntity("aaa");
    FrameBufferSpecification spec;
    spec.Height = 1280;
    spec.Width = 720;
    m_FrameBuffer = FrameBuffer::Create(spec);
}

void EditorLayer::OnEvent(Event &e)
{
    m_OrthographicCameraController.OnEvent(e);
}