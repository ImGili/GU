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
    // m_Vertexbuffer->Bind();
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_b);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    m_Shader->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ExampleLayer::OnAttach()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
    };

    glGenBuffers(1, &m_b);
    glBindBuffer(GL_ARRAY_BUFFER, m_b);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // float vertices[3 * 3] = {
    // 	-0.5f, -0.5f, 0.0f,
    // 	 0.5f, -0.5f, 0.0f,
    // 	 0.0f,  0.5f, 0.0f
    // };
    // m_Vertexbuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    m_Shader = Shader::Create("aaa", "assets/shaders/test.vert", "assets/shaders/test.frag");
}

ExampleLayer::ExampleLayer()
    : Layer("ExampleLayer")
{
}
ExampleLayer::~ExampleLayer()
{
}
