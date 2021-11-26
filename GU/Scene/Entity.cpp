/*
 * @Author: ImGili
 * @Description: 
 */
#include"Entity.h"
using namespace GU;
Entity::Entity(entt::entity handle, Scene* scene)
    : m_EntityHandle(handle), m_Scene(scene)
{}