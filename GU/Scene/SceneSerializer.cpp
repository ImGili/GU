/*
 * @Author: ImGili
 * @Description: 
 */
#include"Scene/SceneSerializer.h"
#include"Scene/Entity.h"
#include"Scene/Component.h"
#include"Core/Log.h"
#include<yaml-cpp/yaml.h>
#include<fstream>
namespace GU
{

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& vec)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << vec.x << vec.y << vec.z << YAML::EndSeq;
        return out;
    }
    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& vec)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << vec.x << vec.y << vec.z << vec.w << YAML::EndSeq;
        return out;
    }
    SceneSerializer::SceneSerializer(const std::shared_ptr<Scene>& scene)
        : m_Scene(scene)
    {
    }

    static void SerializeEntity(YAML::Emitter& out, Entity& entity)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << "12312321412";
        // TagComponent out
        if (entity.HasComponent<TagComponent>())
        {
            auto& tag = entity.GetComponent<TagComponent>();
            out << YAML::Key << "TagComonent";
            out << YAML::BeginMap;
            out << YAML::Key << "Tag" << YAML::Value << tag.Tag.c_str();
            out << YAML::EndMap;
        }
        
        // TransfromComponent out
        if (entity.HasComponent<TransformComponent>())
        {
            auto& tc = entity.GetComponent<TransformComponent>();
            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap;
            out << YAML::Key << "Translation"   << YAML::Value          << tc.Translation;
            out << YAML::Key << "Scale"         << YAML::Value          << tc.Scale;
            out << YAML::Key << "Rotation"      << YAML::Value          << tc.Rotation;
            out << YAML::EndMap;
        }

        // CameraComponent out
        if (entity.HasComponent<CameraComponent>())
        {
            auto& cc = entity.GetComponent<CameraComponent>();
            auto& camera = cc.Camera;
            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap;

            // Camera
            out << YAML::Key << "Camera";
            out << YAML::BeginMap;
            out << YAML::Key << "OrthographicSize"      << YAML::Value          << camera.GetOrthographicSize();
            out << YAML::Key << "OrthographicNearClip"  << YAML::Value          << camera.GetOrthographicNearClip();
            out << YAML::Key << "OrthographicFarClip"   << YAML::Value          << camera.GetOrthographicFarClip();
            out << YAML::EndMap;

            // primary
            out << YAML::Key << "Primary"               << YAML::Value          << cc.Primary;
            out << YAML::EndMap;
        }

        // SpriteComponent out
        if (entity.HasComponent<SpriteRendererComponent>())
        {
            auto& spriteComponent = entity.GetComponent<SpriteRendererComponent>();
            out << YAML::Key << "SpriteComponent";
            out << YAML::BeginMap;
            out << YAML::Key << "Color" << YAML::Value << spriteComponent.Color;
            out << YAML::EndMap;
        }
        
        out << YAML::EndMap;
    }

    bool SceneSerializer::Serializer(const char* filepath)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << "Utitled";
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        m_Scene->m_Registry.each([&](auto entityID){
            Entity entity = { entityID, m_Scene.get() };
            if (!entity)
                return false;
            SerializeEntity(out, entity);
        });
        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(filepath);
        fout << out.c_str();
        return true;
    }

    bool SceneSerializer::Deserializer(const char* filepath)
    {
        
    }

}