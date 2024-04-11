#pragma once

#include <glm/glm.hpp>

#include "Global.h"

class Camera 
{
public:
    Camera();
    ~Camera();

    void SetPosition(const glm::vec3& position);
    void SetTarget(const glm::vec3& target);
    void SetUpVector(const glm::vec3& up);

    // void rotate(GLfloat pitch, GLfloat yaw);
    void Translate(const glm::vec3& offset);

    void SetPerspectiveProjection(float aspectRatio, float fov_deg = 45.0f, float near = 0.1f, float far = 100.f);
    void SetOrthographicProjection(float left = 0.f, float right = (float)Screen::WIDTH, float bottom = Screen::HEIGHT, float top = 0.f, float near = -1.f, float far = 10.f);
    void CalculateViewMatrix();

    glm::vec3 GetPosition() const;
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

public:
    bool needCalculateViewMatrix;

private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_upVector;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

};
