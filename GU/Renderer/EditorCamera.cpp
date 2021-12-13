/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/EditorCamera.h"
#include"Core/Input.h"
#include"Core/Log.h"
#include<glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include<algorithm>
using namespace GU;
EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
    : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), Camera(glm::perspective((float)glm::radians(fov), aspectRatio, nearClip, farClip))
{
    UpdateView();
}

EditorCamera::EditorCamera()
    : m_FOV(45.0), m_AspectRatio(1.778f), m_NearClip(0.1f), m_FarClip(1000.0f), Camera(glm::perspective((float)glm::radians(45.0f), 1.778f, 0.1f, 1000.0f))
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

void EditorCamera::UpdateProjection()
{
    m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
    m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
}

glm::vec3 EditorCamera::CalculatePosition()
{
    return m_FocalPoint - GetForwardDirection() * m_Distance;
}

void EditorCamera::OnUpdate(TimeStep ts)
{
    if (Input::IsKeyPressed((Key::LeftAlt)))
    {
        const glm::vec2& mouse{ Input::GetMoudsePosition().x, Input::GetMoudsePosition().y };
        glm::vec2 delta = ( mouse - m_InitialMousePosition ) * (float)ts;
        m_InitialMousePosition = mouse;
        if (Input::IsMousePressed(MouseKey::ButtonMiddle))
            MousePan(delta);
        else if(Input::IsMousePressed(MouseKey::ButtonLeft))
            MouseRotate(delta);
    }
    UpdateView();
}

void EditorCamera::OnEvent(Event& e)
{
    if (e.GetEventType() == EventType::MouseScrolledEvent)
    {
        OnMouseScroll(static_cast<MouseScrolledEvent&>(e));
    }
}

std::pair<float, float> EditorCamera::PanSpeed() const
{
    float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
    float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

    float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
    float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

    return { xFactor, yFactor };
}

void EditorCamera::MousePan(const glm::vec2& delta)
{
    auto [xSpeed, ySpeed] = PanSpeed();
    m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
    m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
}

void EditorCamera::MouseRotate(const glm::vec2& delta)
{
    float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
    m_Yaw += yawSign * delta.x * 0.8f;
    m_Pitch += delta.y * 0.8f;
}

void EditorCamera::MouseZoom(float delta)
{
    m_Distance -= delta * ZoomSpeed();
    if (m_Distance < 1.0f)
    {
        m_FocalPoint += GetForwardDirection();
        m_Distance = 1.0f;
    }
}

float EditorCamera::ZoomSpeed() const
{
    float distance = m_Distance * 0.2f;
    distance = std::max(distance, 0.0f);
    float speed = distance * distance;
    speed = std::min(speed, 100.0f); // max speed = 100
    return speed;
}

void EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
{
    float delta = e.GetYOffset() * 0.1f;
    MouseZoom(delta);
    UpdateView();
}