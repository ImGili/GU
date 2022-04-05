/*
 * @Author: ImGili
 * @Description: 
 */
#include "Example3DLayer.h"
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
#include "Scene/Scene.h"
#include "Scene/Component.h"
#include <imgui.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
void Example3DLayer::OnImGuiRender()
{

}
void Example3DLayer::OnUpdate(TimeStep ts)
{
    m_EditorCamera.OnUpdate(ts);

    RenderCommand::Clear();

    Renderer3D::BeginScene(m_EditorCamera);
    Renderer3D::DrawModel(m_Model);
    Renderer3D::EndScene();
}

void Example3DLayer::OnEvent(Event& e)
{
    m_EditorCamera.OnEvent(e);
}

void Example3DLayer::OnAttach()
{
    m_Model = Model::Create("assets/models/nanosuit/nanosuit.obj");
}

Example3DLayer::Example3DLayer()
    : Layer("Example3DLayer"), m_EditorCamera(45.0f, 1.778f, 0.1f, 1000.0f)
{
}
Example3DLayer::~Example3DLayer()
{
}
