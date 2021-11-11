/*
 * @Author: ImGili
 * @Description: 
 */
#include "ExampleLayer.h"
#include "Core/Assert.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include <imgui.h>
#include <iostream>
#include <glad/glad.h>
void ExampleLayer::OnImGuiRender()
{
    ImGui::Begin("test");

    ImGui::End();
}
void ExampleLayer::OnUpdate()
{
    
}

void ExampleLayer::OnAttach()
{

    float vertices[3 * 3] = {
    	-0.5f, -0.5f, 0.0f,
    	 0.5f, -0.5f, 0.0f,
    	 0.0f,  0.5f, 0.0f
    };
    m_Vertexbuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    m_Shader = Shader::Create("aaa", "assets/shaders/test.vert", "assets/shaders/test.frag");
}

ExampleLayer::ExampleLayer()
    : Layer("ExampleLayer")
{
}
ExampleLayer::~ExampleLayer()
{
}
