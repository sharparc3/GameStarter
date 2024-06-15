#pragma once

#include <glm/glm.hpp>

#include "Config.h"

struct OrthoFrustum
{
    float left;
    float right;
    float top;
    float bottom;
    float near;
    float far;
};

class Camera 
{
public:
    Camera();
    ~Camera();

    void SetPosition(const glm::vec3& position);
    void SetTarget(const glm::vec3& target);
    void SetUpVector(const glm::vec3& up);

    void Translate(const glm::vec3& offset);

    void SetPerspectiveProjection(float aspectRatio, float fov_deg = 45.0f, float near = 0.1f, float far = 100.f);
    void SetOrthographicProjection(float left, float right, float top, float bottom, float near = -1.f, float far = 100.f);
    void CalculateViewMatrix();
    const OrthoFrustum& GetCameraFrustum() { return m_frustum; };

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

    OrthoFrustum m_frustum;
    std::string m_cameraType;
};
