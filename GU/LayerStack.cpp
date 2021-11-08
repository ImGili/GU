/*
 * @Author: ImGili
 * @Description: 
 */
#include"LayerStack.h"
#include<algorithm>
using namespace GU;
void LayerStack::PushLayer(Layer* layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    layer->OnAttach();
    m_LayerInsertIndex++;
}
void LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
    if (it != m_Layers.begin() + m_LayerInsertIndex)
    {
        layer->OnDetach();
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}
LayerStack::~LayerStack()
{
    for (Layer* layer : m_Layers)
    {
        layer->OnDetach();
        delete layer;
    }
    
}
