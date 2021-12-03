/*
 * @Author: ImGili
 * @Description: 
 */
#include"Scene/SceneCamera.h"
#include<glm/gtc/matrix_transform.hpp>
using namespace GU;
void SceneCamera::ReCalculateProjection()
{
    float orthoLeft     =   -m_OrthographicSize * m_AspectRatio * 0.5f;
    float orthoRight    =   m_OrthographicSize * m_AspectRatio * 0.5f;
    float orthoBottom   =   -m_OrthographicSize * 0.5;
    float orthoTop      =   m_OrthographicSize * 0.5;
    m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
}

void SceneCamera::SetViewPortSize(uint32_t width, uint32_t height)
{
    m_AspectRatio = (float)width / (float)height;
    ReCalculateProjection();
}

void SceneCamera::SetOrthographic(float size, float near, float far)
{
    m_OrthographicSize = size;
    m_OrthographicNear = near;
    m_OrthographicFar = far;
    ReCalculateProjection();
}
