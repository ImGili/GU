/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/Renderer2D.h"
#include"Renderer/VertexArray.h"
#include"Renderer/Buffer.h"
#include"Renderer/Shader.h"

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<memory>
using namespace GU;


struct QuadVertex
{
    glm::vec4 Position;
};

struct Renderer2DData
{
    static const uint32_t MaxQuad = 2000;
    static const uint32_t MaxVertics = MaxQuad * 4;
    QuadVertex* QuadVertexBufferDataBase = nullptr;
    QuadVertex* QuadVertexBufferDataPtr = nullptr;

    glm::vec4 QuadVertexPositions[4];

    std::shared_ptr<VertexBuffer> QuadVertexBuffer;
    std::shared_ptr<VertexArray> QuadVertexArray;
    std::shared_ptr<Shader> QuadVertexShader;
};

static Renderer2DData s_Data;

void Renderer2D::Init()
{
    s_Data.QuadVertexBuffer = VertexBuffer::Create(4);
    s_Data.QuadVertexArray = VertexArray::Create();

    s_Data.QuadVertexBuffer->SetLayout({
        {ShaderDataType::Float3, "a_Position"}
    });

    s_Data.QuadVertexShader = Shader::Create("quadShader", "asset/shaders/texture/vertex.vert", "asset/shaders/texture/fragment.frag");
    s_Data.QuadVertexBufferDataBase = new QuadVertex[Renderer2DData::MaxVertics];

    s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
}

void Renderer2D::BeginScene()
{
    s_Data.QuadVertexBufferDataPtr = s_Data.QuadVertexBufferDataBase;
}

void Renderer2D::DrawQuad(const glm::mat4& transform)
{
    for (size_t i = 0; i < 4; i++)
    {
        s_Data.QuadVertexBufferDataPtr->Position  = transform * s_Data.QuadVertexPositions[i];
        s_Data.QuadVertexBufferDataPtr++;
    }
}

void Renderer2D::EndScene()
{
    Flush();
}

void Renderer2D::Flush()
{
    uint32_t datasize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferDataPtr - (uint8_t*)s_Data.QuadVertexBufferDataBase);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferDataBase, datasize);
}
