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
#include "Renderer/RenderCommand.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer3D.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include <imgui.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
void ExampleLayer::OnImGuiRender()
{
//     static bool p_open = true;

//     ImGui::Begin("DockSpace Demo", &p_open);

//     ImGui::End();
}
void ExampleLayer::OnUpdate(TimeStep ts)
{
    // m_VertexArray->Bind();
    // m_Mesh->GetVertexArray()->Bind();
    m_Shader->Bind();
    m_Shader->SetMat4("u_ProjectionViewMatrix", glm::mat4(1));
    Renderer::Submit(m_Shader, m_VertexArray);
}

void ExampleLayer::OnEvent(Event& e)
{
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
    uint32_t indics[] = 
    {
        0, 1, 2
    };
    std::shared_ptr<IndexBuffer> indexbuffer = IndexBuffer::Create(indics, 3);
    m_Vertexbuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_Vertexbuffer);
    m_VertexArray->SetIndexBuffer(indexbuffer);
    m_Shader = Shader::Create("flatColor", "assets/shaders/flatColor/vertex.vert", "assets/shaders/flatColor/fragment.frag");
}

ExampleLayer::ExampleLayer()
    : Layer("ExampleLayer")
{
}
ExampleLayer::~ExampleLayer()
{
}
