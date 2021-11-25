/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Mesh.h"
using namespace GU;
Mesh::Mesh(const std::vector<MeshVertex>& vdata,const std::vector<uint32_t>& idata)
{
    m_MeshVertexs = vdata;
    m_MeshIndices = idata;

    m_IndexBuffer = IndexBuffer::Create(idata.data(), idata.size());
    m_VertexBuffer = VertexBuffer::Create(vdata.size()*sizeof(MeshVertex));
    m_VertexBuffer->SetData(vdata.data(), vdata.size()*sizeof(MeshVertex));
    m_VertexBuffer->SetLayout({
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float2, "a_TexCoord" }
    });
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

std::shared_ptr<Mesh> Mesh::Create(const std::vector<MeshVertex>& vdata,const std::vector<uint32_t>& idata)
{
    return std::make_shared<Mesh>(vdata, idata);
}