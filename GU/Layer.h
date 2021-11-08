/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core.h"
#include"Events/Event.h"
#include<string>
namespace GU
{
    class GU_API Layer
    {
    public:
        Layer(const char* name);
        virtual ~Layer() = default;

        virtual void OnAttach(){}
        virtual void OnUpdate(){}
        virtual void OnEvent(Event& e){}
        virtual void OnDetach(){}
        virtual void OnImGuiRender(){}
    private:
        std::string m_layer_name;
    };
}