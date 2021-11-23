/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Renderer3D.h"
#include"Renderer/Renderer.h"
#include"Renderer/Shader.h"
#include"Core/Log.h"
using namespace GU;

struct Renderer3DData
{
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Mesh> m_Mesh;
};

static Renderer3DData s_Data;

void Renderer3D::Init()
{
    GU_INFO("Renderer3D init()");
    s_Data.m_Shader = Shader::Create("MeshShader", "assets/shaders/mesh/vertex.vert", "assets/shaders/mesh/fragment.frag");
}

void Renderer3D::BeginScene()
{

}
void Renderer3D::DrawMesh(const std::shared_ptr<Mesh>& Mesh)
{
    s_Data.m_Mesh = Mesh;
}

void Renderer3D::EndScene()
{
    Flush();
}

void Renderer3D::Flush()
{
    Renderer::Submit(s_Data.m_Shader, s_Data.m_Mesh->GetVertexArray());
}