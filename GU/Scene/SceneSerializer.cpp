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

namespace YAML
{
    template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

    template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

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
            out << YAML::Key << "SpriteRendererComponent";
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
            return true;
        });
        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(filepath);
        fout << out.c_str();
        return true;
    }

    bool SceneSerializer::Deserializer(const char* filepath)
    {
        YAML::Node node;
        try
        {
            node = YAML::LoadFile(filepath);
        }
        catch(const std::exception& e)
        {
            GU_ERROR("{0}", e.what());
        }
        std::string sceneName = node["Scene"].as<std::string>();
        GU_INFO("deserialize scene {0}", sceneName);

        auto entities = node["Entities"];
        for (auto entity : entities)
        {
            // Create Entity
            std::string name;
            auto tagComponent = entity["TagComonent"];
            if (tagComponent)
                name = tagComponent["Tag"].as<std::string>();
            
            GU_INFO("Deserialize Entity name: {0}", name);

            Entity deserializeEntity = m_Scene->CreateEntity(name);

            // set transform component
            auto transform = entity["TransformComponent"];
            if (transform)
            {
                auto& tc = deserializeEntity.GetComponent<TransformComponent>();
                tc.Translation = transform["Translation"].as<glm::vec3>();
                tc.Scale = transform["Scale"].as<glm::vec3>();
                tc.Rotation = transform["Rotation"].as<glm::vec3>();
            }
            
            // set SpriteRendererComponent
            auto sprite = entity["SpriteRendererComponent"];
            if (sprite)
            {
                auto& sc = deserializeEntity.AddComponent<SpriteRendererComponent>();
                sc.Color = sprite["Color"].as<glm::vec4>();
            }

            // set CameraComponent
            auto cameraComponent = entity["CameraComponent"];
            if (cameraComponent)
            {
                auto& cc = deserializeEntity.AddComponent<CameraComponent>();
                auto cameraProps = cameraComponent["Camera"];
                cc.Primary = cameraComponent["Primary"].as<bool>();
                cc.Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
                cc.Camera.SetOrthographicNearClip(cameraProps["OrthographicNearClip"].as<float>());
                cc.Camera.SetOrthographicFarClip(cameraProps["OrthographicFarClip"].as<float>());
            }
        }
        
    }

}