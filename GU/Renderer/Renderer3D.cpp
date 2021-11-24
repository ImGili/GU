/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Renderer3D.h"
#include"Renderer/Renderer.h"
#include"Renderer/UniformBuffer.h"
#include"Renderer/Shader.h"
#include"Core/Log.h"
using namespace GU;

struct Renderer3DData
{
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Mesh> m_Mesh;

    struct CameraData
    {
        glm::mat4 ProjectionView;
    };
    CameraData CameraUniformBufferData;
    std::shared_ptr<UniformBuffer> CameraUniformBuffer;
};

static Renderer3DData s_Data;

void Renderer3D::Init()
{
    GU_INFO("Renderer3D init()");
    s_Data.m_Shader = Shader::Create("MeshShader", "assets/shaders/mesh/vertex.vert", "assets/shaders/mesh/fragment.frag");
    s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer3DData::CameraData), 0);
}

void Renderer3D::BeginScene(EditorCamera camera)
{
    s_Data.CameraUniformBufferData.ProjectionView = camera.GetProjectionViewMatrix();
    s_Data.CameraUniformBuffer->SetData(&s_Data.CameraUniformBufferData,sizeof(s_Data.CameraUniformBufferData));
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
    s_Data.CameraUniformBuffer->Bind();
    Renderer::Submit(s_Data.m_Shader, s_Data.m_Mesh->GetVertexArray());
}