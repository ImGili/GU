/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"glm/glm.hpp"
namespace GU
{
    class GU_API EditorCamera
    {
    public:
        EditorCamera();
        EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

        const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionMatrix*m_ViewMatrix; }
    private:
        float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;
        float m_Pitch = 0.0f, m_Yaw = 0.0f;

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;

        glm::vec3 m_Position = {0.0, 0.0, 0.0};

        glm::vec3 m_FocalPoint = {0.0, 0.0, 0.0};
        float m_Distacne = 10.0;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;

        void UpdateView();
        void UpdateProjeciton();

        glm::quat GetOrientation() const;
        glm::vec3 GetForwardDirection() const;
        glm::vec3 GetRightDirection() const;
        glm::vec3 GetUpDirection() const;
        glm::vec3 CalculatePosition();
    };
}