#pragma once
#include"Core/Layer.h"
using namespace GU;
class ExampleLayer : public Layer
{
public:
    ExampleLayer();
    ~ExampleLayer();
    void OnImGuiRender() override;
};