/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Scene/Scene.h"
#include<memory>
namespace GU
{
    class SceneSerializer
    {
    public:
        SceneSerializer(const std::shared_ptr<Scene>& scene);
        bool Serializer(const char* filepath);
        bool Deserializer(const char* filepath);
    private:
        std::shared_ptr<Scene> m_Scene;
    };
}