/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Renderer3D.h"
#include"Renderer/Renderer.h"
#include"Renderer/UniformBuffer.h"
#include"Renderer/Shader.h"
#include"Renderer/Model.h"
#include"Core/Log.h"
using namespace GU;

struct Renderer3DData
{
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Model> m_Model;

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
    s_Data.m_Shader = Shader::Create("MeshShader", "assets/shaders/model/vertex.vert", "assets/shaders/model/fragment.frag");
    s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer3DData::CameraData));
}

void Renderer3D::BeginScene(EditorCamera camera)
{
    s_Data.CameraUniformBufferData.ProjectionView = camera.GetProjectionViewMatrix();
    s_Data.CameraUniformBuffer->SetData(&s_Data.CameraUniformBufferData,sizeof(s_Data.CameraUniformBufferData));
}
void Renderer3D::DrawModel(const std::shared_ptr<Model>& model)
{
    s_Data.m_Model = model;
}

void Renderer3D::EndScene()
{
    Flush();
}

void Renderer3D::Flush()
{
    s_Data.CameraUniformBuffer->Bind();
    for (size_t i = 0; i < s_Data.m_Model->GetMeshs().size(); i++)
    {
        s_Data.m_Model->GetMeshs()[i]->GetTexture()->Bind(0);
        Renderer::Submit(s_Data.m_Shader, s_Data.m_Model->GetMeshs()[i]->GetVertexArray());
    }
}