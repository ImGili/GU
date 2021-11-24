/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/EditorCamera.h"
#include<glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
using namespace GU;
EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
    : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), m_ProjectionMatrix(glm::perspective((float)glm::radians(fov), aspectRatio, nearClip, farClip))
{
    UpdateView();
}

EditorCamera::EditorCamera()
    : m_FOV(45.0), m_AspectRatio(1.778f), m_NearClip(0.1f), m_FarClip(1000.0f), m_ProjectionMatrix(glm::perspective((float)glm::radians(45.0f), 1.778f, 0.1f, 1000.0f))
{
    UpdateView();
}

glm::quat EditorCamera::GetOrientation() const
{
    return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
}

glm::vec3 EditorCamera::GetForwardDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 EditorCamera::GetRightDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(1.0, 0.0, 0.0));
}

glm::vec3 EditorCamera::GetUpDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(0.0, 1.0, 0.0));
}

void EditorCamera::UpdateView()
{
    m_Position = CalculatePosition();

    glm::quat orientation = GetOrientation();

    m_ViewMatrix = glm::translate(glm::mat4(1), m_Position) *  glm::toMat4(orientation);
    m_ViewMatrix = glm::inverse(m_ViewMatrix);
}

void EditorCamera::UpdateProjeciton()
{
    m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
    m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
}

glm::vec3 EditorCamera::CalculatePosition()
{
    return m_FocalPoint - GetForwardDirection() * m_Distacne;
}