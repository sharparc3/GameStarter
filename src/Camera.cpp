#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera()
{
    m_target = glm::vec3(0.f, 0.f, -1.f);
    m_upVector = glm::vec3(0.f, 1.f, 0.f);
    m_position = glm::vec3(0.f, 0.f, 0.f);
    m_viewMatrix = glm::mat4(1.f);
    m_projectionMatrix = glm::mat4(1.f);
    needCalculateViewMatrix = true;
}

Camera::~Camera()
{
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_position = position;
    needCalculateViewMatrix = true;
}

void Camera::SetTarget(const glm::vec3& target)
{
    m_target = target;
    needCalculateViewMatrix = true;
}

void Camera::SetUpVector(const glm::vec3& up)
{
    m_upVector = up;
    needCalculateViewMatrix = true;
}

void Camera::Translate(const glm::vec3& offset)
{
    m_position += offset;
    needCalculateViewMatrix = true;
}

void Camera::SetPerspectiveProjection(float fov_deg, float aspectRatio, float near, float far)
{
    m_projectionMatrix = glm::perspective(glm::radians(fov_deg), aspectRatio, near, far);
}

void Camera::SetOrthographicProjection(float left, float right, float top, float bottom, float near, float far)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

glm::vec3 Camera::GetPosition() const
{
    return m_position;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return m_viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return m_projectionMatrix;
}

void Camera::CalculateViewMatrix()
{
    m_viewMatrix = glm::lookAt(m_position, m_target, m_upVector);
    needCalculateViewMatrix = false;
}
