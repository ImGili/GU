/*
 * @Author: ImGili
 * @Description: 正交相机
 */
#include"Renderer/OrthographicCamera.h"
#include<glm/gtc/matrix_transform.hpp>
using namespace GU;
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1)
{
    m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1), m_Position) * glm::rotate(glm::mat4(1), glm::radians(m_Rotation), glm::vec3(0,0,1));

    m_ViewMatrix = glm::inverse(transform);

    m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
