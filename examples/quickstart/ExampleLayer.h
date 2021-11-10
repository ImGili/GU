#pragma once
#include"Core/Layer.h"
#include"Renderer/Shader.h"
#include"Renderer/Buffer.h"
using namespace GU;
class ExampleLayer : public Layer
{
public:
    ExampleLayer();
    ~ExampleLayer();
    void OnImGuiRender() override;
    void OnAttach() override;
    void OnUpdate() override;
private:
    std::shared_ptr<Shader> m_Shader;
    uint32_t m_b;
    std::shared_ptr<VertexBuffer> m_Vertexbuffer;
};