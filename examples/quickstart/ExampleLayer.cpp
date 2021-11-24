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
#include "Renderer/Model.h"
#include <imgui.h>
#include <iostream>
#include <glad/glad.h>
void ExampleLayer::OnImGuiRender()
{
//     static bool p_open = true;

//     ImGui::Begin("DockSpace Demo", &p_open);

//     ImGui::End();
}
void ExampleLayer::OnUpdate(TimeStep ts)
{
    // m_VertexArray->Bind();
    // m_Shader->Bind();
    // RenderCommand::DrawIndexed(m_VertexArray);
    Renderer3D::BeginScene();
    Renderer3D::DrawMesh(m_Mesh);
    Renderer3D::EndScene();
}

void ExampleLayer::OnAttach()
{
    std::shared_ptr<Model> model= Model::Create("assets/models/test.obj");
    std::vector<MeshVertex> meshVertex;
    std::vector<uint32_t> meshIndics;
    meshVertex.push_back({{-0.5f, -0.5f, 0.0f}});
    meshVertex.push_back({{0.5f, -0.5f, 0.0f}});
    meshVertex.push_back({{0.0f,  0.5f, 0.0f}});
    meshIndics.push_back(0);
    meshIndics.push_back(1);
    meshIndics.push_back(2);
    // m_Mesh = Mesh::Create(meshVertex, meshIndics);
    m_Mesh = model->GetMesh();
    m_VertexArray = VertexArray::Create();
    float vertices[3 * 3] = {
    	-0.5f, -0.5f, 0.0f,
    	 0.5f, -0.5f, 0.0f,
    	 0.0f,  0.5f, 0.0f
    };
    m_Vertexbuffer = VertexBuffer::Create(meshVertex.data(), meshVertex.size()*sizeof(MeshVertex));
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
    m_Shader = Shader::Create("aaa", "assets/shaders/test.vert", "assets/shaders/test.frag");
}

ExampleLayer::ExampleLayer()
    : Layer("ExampleLayer")
{
}
ExampleLayer::~ExampleLayer()
{
}
