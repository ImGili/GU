/*
 * @Author: ImGili
 * @Description: Editor UI 
 */
#pragma once
#include"Core/Layer.h"
#include<string>
using namespace GU;

class EditorLayer : public Layer
{
public:
    EditorLayer();
    ~EditorLayer() = default;

    void OnUpdate() override;
    void OnImGuiRender() override;
private:
};
