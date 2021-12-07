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
using namespace GU;
SceneSerializer::SceneSerializer(const std::shared_ptr<Scene>& scene)
    : m_Scene(scene)
{
}

static void SerializeEntity(YAML::Emitter& out, Entity& entity)
{
    out << YAML::BeginMap;
    out << YAML::Key << "Entity" << YAML::Value << YAML::BeginSeq;
    // tag out
    out << YAML::BeginMap << YAML::Key << "Tag" << YAML::Value << entity.GetComponent<TagComponent>().Tag.c_str() << YAML::EndMap;

    // transfrom out
    if (entity.HasComponent<TransformComponent>())
    {

    }
    
    out << YAML::EndSeq;
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
    GU_INFO("{0}", out.c_str());
    return true;
}

bool SceneSerializer::Deserializer(const char* filepath)
{

}