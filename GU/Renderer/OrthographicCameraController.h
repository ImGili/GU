/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/TimeStep.h"
#include"Events/Event.h"
#include"Events/MouseEvent.h"
#include"Renderer/OrthographicCamera.h"
#include"glm/glm.hpp"
namespace GU
{
    class GU_API OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);
        const OrthographicCamera& GetCamera() const { return m_OrthographicCamera;}
        void OnUpdate(TimeStep ts);
        void OnEvent(Event& e);
        void OnMouseScrolled(Event& e);
    private:
        OrthographicCamera m_OrthographicCamera;
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        glm::vec3 m_CameraPosition = glm::vec3(0, 0, 1);
        float m_CameraTranslationSpeed = 5.0f;
    };
}