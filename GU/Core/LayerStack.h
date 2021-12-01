/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include "Core.h"
#include "Layer.h"
#include <vector>
namespace GU
{
    class LayerStack
    {
    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex;
    public:
        LayerStack(/* args */) = default;
        void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
        ~LayerStack();
    };
}

