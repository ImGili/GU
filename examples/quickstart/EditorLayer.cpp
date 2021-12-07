/*
 * @Author: ImGili
 * @Description: 
 */
#include "EditorLayer.h"
#include "Core/Application.h"
#include "Core/Input.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/RenderCommand.h"
#include "ImGui/ImGuiAppConsole.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include"Scene/Component.h"
#include"Scene/Scene.h"
#include"Scene/Entity.h"
#include"Scene/ScriptableEntity.h"
#include"Scene/SceneSerializer.h"
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
        m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
    }
    m_FrameBuffer->Bind();
    RenderCommand::Clear();
    // Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());
    m_ActiveScene->OnUpdate(ts);
    // Renderer2D::DrawQuad(glm::vec2(0.0, 0.0), glm::vec4(1.0, 1.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(-5.0, 5.0), glm::vec4(1.0, 1.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(5.0, 5.0), glm::vec4(0.0, 1.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(-5.0, -5.0), glm::vec4(1.0, 0.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(5.0, -5.0), glm::vec4(1.0, 1.0, 0.0, 1.0));
    // Renderer2D::EndScene();
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
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinStyle = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    style.WindowMinSize.x = minWinStyle;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                Application::Get()->Close();

            if (ImGui::MenuItem("Open...", "Ctrl+O"))
            {
                SceneSerializer sceneserializer(m_ActiveScene);
                sceneserializer.Deserializer("assets/scenes/test.gu");
            }

            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
            {
                SceneSerializer sceneserializer(m_ActiveScene);
                sceneserializer.Serializer("assets/scenes/test.gu");
            }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    // {
    //     ImGui::Begin("Editor");
    //     // Select Camera
    //     static int cameraSelected = -1;
    //     if(ImGui::Selectable("Cmaera A", cameraSelected == 1))
    //     {
    //         m_CameraEntity.GetComponent<CameraComponent>().Primary = true;
    //         m_SecondCameraEntity.GetComponent<CameraComponent>().Primary = false;
    //         cameraSelected = 1;
    //     }
    //     if(ImGui::Selectable("Cmaera B", cameraSelected == 2))
    //     {
    //         m_CameraEntity.GetComponent<CameraComponent>().Primary = false;
    //         m_SecondCameraEntity.GetComponent<CameraComponent>().Primary = true;
    //         cameraSelected = 2;
    //     }
    //     static float cameraOrthoSize = 15.0f;
    //     ImGui::DragFloat("OrthoSize", &cameraOrthoSize, 0.1, 0.0f, 20.0f);
    //     m_SecondCameraEntity.GetComponent<CameraComponent>().Camera.SetOrthographicSize(cameraOrthoSize);
    //     ImGui::End();
    // }

    m_SceneHierarchyPanel.OnImGuiRender();
    // {
    //     ImGui::ShowDemoWindow();
    // }

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

#if 0
    m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
    auto& cc = m_CameraEntity.AddComponent<CameraComponent>();

    m_SecondCameraEntity = m_ActiveScene->CreateEntity("Camera B");
    m_SecondCameraEntity.AddComponent<CameraComponent>();
    auto& scc = m_SecondCameraEntity.GetComponent<CameraComponent>();
    scc.Primary = false;
    class CameraController : public ScriptableEntity
    {
    public:
        virtual ~CameraController() = default;

        virtual void OnCreate() {}
        virtual void OnUpdate(TimeStep ts) {
            auto& translation = GetComponent<TransformComponent>().Translation;
            float speed = 5.0f;
            if(Input::IsKeyPressed(KeyCode::A))
                translation.x -= speed * ts;
            if(Input::IsKeyPressed(KeyCode::D))
                translation.x += speed * ts;
            if(Input::IsKeyPressed(KeyCode::S))
                translation.y -= speed * ts;
            if(Input::IsKeyPressed(KeyCode::W))
                translation.y += speed * ts;
        }
        virtual void OnDestroy() {}
    };

    m_SecondCameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();

    Entity entity1 = m_ActiveScene->CreateEntity();
    entity1.AddComponent<SpriteRendererComponent>(glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
    auto& transform1 = entity1.GetComponent<TransformComponent>().Translation;
    transform1 = { 0.0, 0.0, 0.0 };
    Entity entity2 = m_ActiveScene->CreateEntity();
    entity2.AddComponent<SpriteRendererComponent>(glm::vec4{1.0f, 0.0f, 0.0f, 1.0f});
    auto& sprite = entity2.GetComponent<SpriteRendererComponent>();
    sprite.Texture = Texture2D::Create("assets/textures/container2.png");
    auto& transform2 = entity2.GetComponent<TransformComponent>().Translation;
    transform1 = { 1.0, 1.0, 0.0 };
    Entity entity3 = m_ActiveScene->CreateEntity();
    entity3.AddComponent<SpriteRendererComponent>(glm::vec4{0.0f, 0.0f, 1.0f, 1.0f});
    auto& transform3 = entity3.GetComponent<TransformComponent>().Translation;
    transform3 = { -1.0, -1.0, 0.0 };
#endif
    m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    
    FrameBufferSpecification spec;
    spec.Height = 1280;
    spec.Width = 720;
    m_FrameBuffer = FrameBuffer::Create(spec);


    
}

void EditorLayer::OnEvent(Event &e)
{
    m_OrthographicCameraController.OnEvent(e);
}