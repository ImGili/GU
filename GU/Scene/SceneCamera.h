/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Renderer/Camera.h"
namespace GU
{
    class SceneCamera : public Camera
    {
    public:
        SceneCamera() { ReCalculateProjection(); }

        void SetViewPortSize(uint32_t width, uint32_t height);

        void SetOrthographic(float size, float near, float far);

        void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; ReCalculateProjection(); }
        float GetOrthographicNearClip() const { return m_OrthographicNear; }
        void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; ReCalculateProjection(); }
        float GetOrthographicFarClip() const { return m_OrthographicFar; }
        void SetOrthographicSize(float size) { m_OrthographicSize = size; ReCalculateProjection(); }
        float GetOrthographicSize() const { return m_OrthographicSize; }

    private:
        void ReCalculateProjection();
    private:

        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
        float m_AspectRatio = 0.0f;
    };
}