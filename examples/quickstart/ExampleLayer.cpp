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
#include "Renderer/VertexArray.h"
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
    m_VertexArray->Bind();
    m_Shader->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ExampleLayer::OnAttach()
{
    m_VertexArray = VertexArray::Create();
    float vertices[3 * 3] = {
    	-0.5f, -0.5f, 0.0f,
    	 0.5f, -0.5f, 0.0f,
    	 0.0f,  0.5f, 0.0f
    };
    m_Vertexbuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" }
    };
    m_Vertexbuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_Vertexbuffer);
    m_Shader = Shader::Create("aaa", "assets/shaders/test.vert", "assets/shaders/test.frag");
}

ExampleLayer::ExampleLayer()
    : Layer("ExampleLayer")
{
}
ExampleLayer::~ExampleLayer()
{
}
