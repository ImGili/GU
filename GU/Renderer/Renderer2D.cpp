/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Renderer2D.h"
#include"Renderer/VertexArray.h"
#include"Renderer/Buffer.h"
#include"Renderer/UniformBuffer.h"
#include"Renderer/Shader.h"
#include"Renderer/RenderCommand.h"

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<memory>
using namespace GU;


struct QuadVertex
{
    glm::vec3 Position;
};

struct Renderer2DData
{
    static const uint32_t MaxQuad = 2000;
    static const uint32_t MaxVertices = MaxQuad * 4;
    static const uint32_t MaxIndices = MaxQuad * 6;
    QuadVertex* QuadVertexBufferDataBase = nullptr;
    QuadVertex* QuadVertexBufferDataPtr = nullptr;

    glm::vec4 QuadVertexPositions[4];

    std::shared_ptr<VertexBuffer> QuadVertexBuffer;
    std::shared_ptr<VertexArray> QuadVertexArray;
    std::shared_ptr<Shader> QuadVertexShader;
    uint32_t QuadIndicesCount = 0;

    struct CameraData
    {
        glm::mat4 ProjectionView;
    };
    CameraData CameraUniformBufferData;
    std::shared_ptr<UniformBuffer> CameraUniformBuffer;

};

static Renderer2DData s_Data;

void Renderer2D::Init()
{
    s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
    s_Data.QuadVertexArray = VertexArray::Create();
    s_Data.QuadVertexBuffer->SetLayout({
        {ShaderDataType::Float3, "a_Position"}
    });
    s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

    s_Data.QuadVertexShader = Shader::Create("quadShader", "assets/shaders/texture/vertex.vert", "assets/shaders/texture/fragment.frag");
    s_Data.QuadVertexBufferDataBase = new QuadVertex[Renderer2DData::MaxVertices];

    s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

    uint32_t* quadIndices = new uint32_t[Renderer2DData::MaxIndices];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < Renderer2DData::MaxIndices; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;

        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }
    std::shared_ptr<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
    s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
    delete[] quadIndices;
    s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_Data.QuadVertexBufferDataPtr = s_Data.QuadVertexBufferDataBase;
    s_Data.QuadIndicesCount = 0;
    s_Data.CameraUniformBufferData.ProjectionView = camera.GetProjecttionViewMatrix();
    s_Data.CameraUniformBuffer->SetData(&s_Data.CameraUniformBufferData,sizeof(s_Data.CameraUniformBufferData));
}

void Renderer2D::DrawQuad(const glm::mat4& transform)
{
    for (size_t i = 0; i < 4; i++)
    {
        s_Data.QuadVertexBufferDataPtr->Position  = s_Data.QuadVertexPositions[i];
        s_Data.QuadVertexBufferDataPtr++;
    }
    s_Data.QuadIndicesCount += 6;
}

void Renderer2D::EndScene()
{
    Flush();
}

void Renderer2D::Flush()
{
    uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferDataPtr - (uint8_t*)s_Data.QuadVertexBufferDataBase);
    s_Data.QuadVertexArray->Bind();
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferDataBase, dataSize);
    s_Data.QuadVertexShader->Bind();
    s_Data.CameraUniformBuffer->Bind();
    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndicesCount);
}
