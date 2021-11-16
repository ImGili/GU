/*
 * @Author: ImGili
 * @Description: 
 */
#include"Renderer/OrthographicCameraController.h"
#include"Core/Input.h"
#include"glm/glm.hpp"
using namespace GU;
OrthographicCameraController::OrthographicCameraController(float aspectRatio)
    : m_AspectRatio(aspectRatio), m_OrthographicCamera(-(aspectRatio/2*10) , (aspectRatio/2*10) , -10, 10), m_CameraPosition({4, 4, 1})
{
    m_OrthographicCamera.SetPosition(m_CameraPosition);
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