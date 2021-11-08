/*
 * @Author: ImGili
 * @Description: 
 */
#include"ImGuiLayer.h"
#include<imgui.h>
#include<backends/imgui_impl_glfw.h>
#include<backends/imgui_impl_opengl3.h>
#include"Core/Application.h"

using namespace GU;

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
{}

void ImGuiLayer::OnAttach()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // ImFont *font = io.Fonts->AddFontFromFileTTF("./fonts/楷体_GB2312.ttf", 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    // io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
    // io.Fonts->GetGlyphRangesChineseFull();

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    GLFWwindow* window = (GLFWwindow*)(Application::Get()->GetWindow().GetNativeWindow());
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
    // imgui
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
