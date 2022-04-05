#pragma once
#include"Core/Layer.h"
#include"Renderer/Shader.h"
#include"Renderer/Buffer.h"
#include"Renderer/VertexArray.h"
#include"Renderer/Model.h"
#include"Renderer/EditorCamera.h"
using namespace GU;
class Example3DLayer : public Layer
{
public:
    Example3DLayer();
    ~Example3DLayer();
    void OnImGuiRender() override;
    void OnAttach() override;
    void OnUpdate(TimeStep ts) override;
    void OnEvent(Event& e) override;
private:
    std::shared_ptr<Model> m_Model;
    EditorCamera m_EditorCamera;
};