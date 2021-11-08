/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core.h"
#include"Layer.h"
#include"Events/Event.h"

namespace GU
{
    class GU_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        void OnAttach() override;
        void OnDetach() override;
        void Begin();
        void End();
    };
}