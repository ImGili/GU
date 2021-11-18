/*
 * @Author: ImGili
 * @Description: 
 */
#include"EditorLayer.h"
#include"Core/Application.h"
#include"Renderer/FrameBuffer.h"
#include"Renderer/RenderCommand.h"
#include"ImGui/ImGuiAppConsole.h"
#include"glm/gtc/type_ptr.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"Renderer/Renderer.h"
#include"Renderer/Renderer2D.h"
#include<imgui.h>
#include<cmath>
#include"GLFW/glfw3.h"
EditorLayer::EditorLayer()
    :Layer("EditorLayer"), m_OrthographicCameraController(1280.0f / 720.0f, 100)
{
}

void EditorLayer::OnUpdate(TimeStep ts)
{
    m_AgentSimulator.OnUpdate();
    if (m_IsViewportFocus)
    {
        m_OrthographicCameraController.OnUpdate(ts);
    }

    if (m_ViewportSize.x != 0 && m_ViewportSize.y !=0)
    {
        m_OrthographicCameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
    }
    m_FrameBuffer->Bind();
    RenderCommand::Clear();
    // m_Shader->Bind();
    // m_Shader->SetMat4("u_ProjectionViewMatrix", m_OrthographicCameraController.GetCamera().GetProjecttionViewMatrix());
    // m_Shader->SetMat4("u_ProjectionViewMatrix", glm::mat4(1));

    // Renderer::Submit(m_Shader, m_VertexArray);

    Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());
    Renderer2D::DrawQuad(glm::vec2(0.0, 0.0), {100.0, 100.0},glm::vec4(1.0, 1.0, 0.0, 1.0));
    m_AgentSimulator.DrawAgents();
    // Renderer2D::DrawQuad(glm::vec2(0.0, 0.0), glm::vec4(1.0, 1.0, 1.0, 1.0));
    // Renderer2D::DrawQuad(glm::vec2(2.0, 0.0), glm::vec4(1.0, 0.0, 1.0, 1.0));
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
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
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
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit")) Application::Get()->Close();
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
    ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    // ImGui::ShowDemoWindow();
    //-----------Debug Console-----------------------------------
    static ImGuiAppConsole console;
    console.Draw("Console", &p_open);

    ImGui::Begin("BrowserPannel");
    ImGui::Button("aaa");
    ImGui::End();


    ImGui::End();
    ImGui::End();
}
void EditorLayer::OnAttach()
{
    // uint32_t f = 200;
    // uint32_t r = 25;
    // for (size_t i = 0; i < f; i++)
    // {
    //     glm::vec2 position = glm::vec2(r*cos(i*(360/f)), r*sin(i*(360/f)));
    //     glm::vec2 goal = glm::vec2(r*cos(i*(360/f) - 180.0), r*sin(i*(360/f)- 180.0));
    //     m_AgentSimulator.AddAgents({
    //     { position, {goal}, {0.0, 0.0, 1.0} },
    //     });
    // }
    m_AgentSimulator.AddAgents({
        { {0.0, 0.0}, {{0.0, 25.0}, {0, 0}}, {0.0, 0.0, 1.0} },
        });
    // Application::Get()->GetWindow().MaxWindow();
    FrameBufferSpecification spec;
    spec.Height = 720;
    spec.Width = 1280;
    m_FrameBuffer = FrameBuffer::Create(spec);

    m_VertexArray = VertexArray::Create();
    float vertices[] = {
    	-0.5f, -0.5f, 0.0f,
    	 0.5f, -0.5f, 0.0f,
    	 0.0f,  0.5f, 0.0f
    };
    m_Vertexbuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" }
    };
    uint32_t indics[] = 
    {
        0, 1, 2
    };
    std::shared_ptr<IndexBuffer> indexbuffer = IndexBuffer::Create(indics, 3);
    m_Vertexbuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_Vertexbuffer);
    m_VertexArray->SetIndexBuffer(indexbuffer);
    m_Shader = Shader::Create("flatColor", "assets/shaders/flatColor/vertex.vert", "assets/shaders/flatColor/fragment.frag");
    // m_Shader->Bind();
    // m_Shader->SetMat4("u_ProjectionViewMatrix", glm::mat4(1));
}

void EditorLayer::OnEvent(Event& e)
{
    m_OrthographicCameraController.OnEvent(e);
}