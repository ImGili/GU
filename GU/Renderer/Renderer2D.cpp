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
#include"Renderer/Texture.h"

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<memory>
using namespace GU;


struct QuadVertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    float TexIndex;
};

struct Renderer2DData
{
    static const uint32_t aQuadIndices = 6;
    static const uint32_t aQuadVertices = 4;
    static const uint32_t MaxQuad = 2000;
    static const uint32_t MaxVertices = MaxQuad * aQuadVertices;
    static const uint32_t MaxIndices = MaxQuad * aQuadIndices;

    static const uint32_t MaxTextureSlots = 32;

    QuadVertex* QuadVertexBufferDataBase = nullptr;
    QuadVertex* QuadVertexBufferDataPtr = nullptr;

    glm::vec4 QuadVertexPositions[4];

    std::shared_ptr<VertexBuffer> QuadVertexBuffer;
    std::shared_ptr<VertexArray> QuadVertexArray;
    std::shared_ptr<Shader> QuadVertexShader;
    uint32_t QuadIndicesCount = 0;

    std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> TextureSlots;
    uint32_t TextureSlotIndex = 1;
    std::shared_ptr<Texture2D> WhiteTexture;

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
        { ShaderDataType::Float3, "a_Position"     },
        { ShaderDataType::Float4, "a_Color"        },
        { ShaderDataType::Float2, "a_TexCoord"     },
        { ShaderDataType::Float,  "a_TexIndex"     }
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

        offset += s_Data.aQuadVertices;
    }
    std::shared_ptr<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
    s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
    delete[] quadIndices;
    s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData));

    s_Data.WhiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
    s_Data.TextureSlots[0] = s_Data.WhiteTexture;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    glDisable(GL_DEPTH_TEST);
    s_Data.QuadVertexBufferDataPtr = s_Data.QuadVertexBufferDataBase;
    s_Data.QuadIndicesCount = 0;
    s_Data.CameraUniformBufferData.ProjectionView = camera.GetProjectionViewMatrix();
    s_Data.CameraUniformBuffer->SetData(&s_Data.CameraUniformBufferData,sizeof(s_Data.CameraUniformBufferData));
}
void Renderer2D::BeginScene(const EditorCamera& camera)
{
    glDisable(GL_DEPTH_TEST);
    s_Data.QuadVertexBufferDataPtr = s_Data.QuadVertexBufferDataBase;
    s_Data.QuadIndicesCount = 0;
    s_Data.CameraUniformBufferData.ProjectionView = camera.GetProjectionViewMatrix();
    s_Data.CameraUniformBuffer->SetData(&s_Data.CameraUniformBufferData,sizeof(s_Data.CameraUniformBufferData));
}

void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
{
    glDisable(GL_DEPTH_TEST);
    s_Data.QuadVertexBufferDataPtr = s_Data.QuadVertexBufferDataBase;
    s_Data.QuadIndicesCount = 0;
    s_Data.CameraUniformBufferData.ProjectionView = camera.GetProjection() * glm::inverse(transform);
    s_Data.CameraUniformBuffer->SetData(&s_Data.CameraUniformBufferData,sizeof(s_Data.CameraUniformBufferData));
}


void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    for (size_t i = 0; i < 4; i++)
    {
        s_Data.QuadVertexBufferDataPtr->Position  = transform * s_Data.QuadVertexPositions[i];
        s_Data.QuadVertexBufferDataPtr->Color  = color;
        s_Data.QuadVertexBufferDataPtr++;
        s_Data.QuadVertexBufferDataPtr->TexIndex = 0;
        s_Data.QuadVertexBufferDataPtr->TexCoord = textureCoords[i];
    }
    s_Data.QuadIndicesCount += s_Data.aQuadIndices;
}

void Renderer2D::EndScene()
{
    Flush();
    glEnable(GL_DEPTH_TEST);
}

void Renderer2D::Flush()
{
    uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferDataPtr - (uint8_t*)s_Data.QuadVertexBufferDataBase);
    s_Data.QuadVertexArray->Bind();
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferDataBase, dataSize);
    s_Data.QuadVertexShader->Bind();
    s_Data.CameraUniformBuffer->Bind();
    for (size_t i = 0; i < s_Data.TextureSlotIndex; i++)
    {
        s_Data.TextureSlots[i]->Bind(i);
    }
    
    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndicesCount);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec4& color)
{
    glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(position.x, position.y, 0));
    DrawQuad(transform, color);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2 size, const glm::vec4& color)
{
    glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(position.x, position.y, 0)) * glm::scale(glm::mat4(1), glm::vec3(size.x, size.y, 1.0));
    DrawQuad(transform, color);
}