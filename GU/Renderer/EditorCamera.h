/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/TimeStep.h"
#include"Events/MouseEvent.h"
#include"glm/glm.hpp"
#include<utility>
namespace GU
{
    class EditorCamera
    {
    public:
        EditorCamera();
        EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

        void OnUpdate(TimeStep ts);
        void OnEvent(Event& e);

        glm::mat4 GetProjectionViewMatrix() const { return m_ProjectionMatrix*m_ViewMatrix;}
    private:
        float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;
        float m_Pitch = 0.0f, m_Yaw = 0.0f;

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;

        glm::vec3 m_Position = {0.0, 0.0, 0.0};

        glm::vec3 m_FocalPoint = {0.0, 0.0, 0.0};
        float m_Distance = 10.0;

        glm::vec2 m_InitialMousePosition = { 0.0, 0.0 };

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;

        void UpdateView();
        void UpdateProjeciton();

        std::pair<float, float> PanSpeed() const;
        void MousePan(const glm::vec2& delta);
        void MouseRotate(const glm::vec2& delta);

        void MouseZoom(float delta);
        float ZoomSpeed() const;

        void OnMouseScroll(MouseScrolledEvent& e);

        glm::quat GetOrientation() const;
        glm::vec3 GetForwardDirection() const;
        glm::vec3 GetRightDirection() const;
        glm::vec3 GetUpDirection() const;
        glm::vec3 CalculatePosition();
    };
}