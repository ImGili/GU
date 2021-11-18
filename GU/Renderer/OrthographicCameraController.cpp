/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/OrthographicCameraController.h"
#include"Events/MouseEvent.h"
#include"Core/Input.h"
#include"glm/glm.hpp"
#include"Core/Log.h"
#include <algorithm>
using namespace GU;
OrthographicCameraController::OrthographicCameraController(float aspectRatio)
    : m_AspectRatio(aspectRatio), m_ZoomLevel(1), m_OrthographicCamera(-aspectRatio * 1, aspectRatio * 1, -1, 1)
{
}
void OrthographicCameraController::OnUpdate(TimeStep ts)
{
    if (Input::IsKeyPressed(KeyCode::A))
    {
        m_CameraPosition.x += m_CameraTranslationSpeed * ts;
    }
    if (Input::IsKeyPressed(KeyCode::D))
    {
        m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
    }
    if (Input::IsKeyPressed(KeyCode::S))
    {
        m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
    }
    if (Input::IsKeyPressed(KeyCode::W))
    {
        m_CameraPosition.y += m_CameraTranslationSpeed * ts;
    }

    m_OrthographicCamera.SetPosition(m_CameraPosition);
}

void OrthographicCameraController::OnEvent(Event& e)
{
    OnMouseScrolled(e);
}

void OrthographicCameraController::OnMouseScrolled(Event& e)
{
    if (e.GetEventType() == EventType::MouseScrolledEvent)
    {
        MouseScrolledEvent& event = static_cast<MouseScrolledEvent&>(e);
        m_ZoomLevel -= event.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_OrthographicCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        event.Handled = true;
        GU_INFO("m_ZoomLevel{0}", m_ZoomLevel);
    }
}

void OrthographicCameraController::OnResize(float width, float height)
{
    m_AspectRatio = width / height;
    m_OrthographicCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}