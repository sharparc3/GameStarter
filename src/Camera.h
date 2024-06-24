#pragma once

#include <glm/glm.hpp>

#include "Config.h"

/**
 * @struct OrthoFrustum
 * @brief Represents the orthographic frustum for a camera.
 */
struct OrthoFrustum
{
    float left;     ///< The left boundary of the frustum.
    float right;    ///< The right boundary of the frustum.
    float top;      ///< The top boundary of the frustum.
    float bottom;   ///< The bottom boundary of the frustum.
    float near;     ///< The near boundary of the frustum.
    float far;      ///< The far boundary of the frustum.
};


/**
 * @class Camera
 * @brief Manages the camera's position, orientation, and projection.
 *
 * This class define the "view box" of the renderer
 * It handles the camera's position, target, up vector, and projection matrices (both perspective and orthographic).
 * 
 */
class Camera 
{
public:
    /**
     * @brief Constructs a Camera object.
     */
    Camera();

    /**
     * @brief Destructor.
     */
    ~Camera();

    /**
     * @brief Sets the camera's position.
     * @param position The new position of the camera.
     */
    void SetPosition(const glm::vec3& position);

    /**
     * @brief Sets the camera's target.
     * @param target The new target of the camera.
     */
    void SetTarget(const glm::vec3& target);

    /**
     * @brief Sets the camera's up vector.
     * @param up The new up vector of the camera.
     */
    void SetUpVector(const glm::vec3& up);

    /**
     * @brief Translates the camera by the given offset.
     * @param offset The offset by which to translate the camera.
     */
    void Translate(const glm::vec3& offset);

    /**
     * @brief Sets the camera to perspective type and define perspective projection matrix.
     * @param aspectRatio The aspect ratio of the projection.
     * @param fov_deg The field of view in degrees (default is 45.0f).
     * @param near The near clipping plane (default is 0.1f).
     * @param far The far clipping plane (default is 100.f).
     */
    void SetPerspectiveProjection(float aspectRatio, float fov_deg = 45.0f, float near = 0.1f, float far = 100.f);

    /**
     * @brief Sets the camera to orthographic type and define the projection matrix. 2D games should use this in most cases.
     * @param left The left boundary of the frustum.
     * @param right The right boundary of the frustum.
     * @param top The top boundary of the frustum.
     * @param bottom The bottom boundary of the frustum.
     * @param near The near clipping plane (default is -1.f).
     * @param far The far clipping plane (default is 100.f).
     */
    void SetOrthographicProjection(float left, float right, float top, float bottom, float near = -1.f, float far = 100.f);

    /**
     * @brief Calculates the view matrix based on the current position, target, and up vector.
     */
    void CalculateViewMatrix();

    /**
     * @brief Gets the camera's orthographic frustum for performing frustum culling.
     * @return A reference to the orthographic frustum.
     */
    const OrthoFrustum& GetCameraFrustum() { return m_frustum; };

    /**
     * @brief Gets the camera's position.
     * @return The current position of the camera.
     */
    glm::vec3 GetPosition() const;

    /**
     * @brief Gets the view matrix.
     * @return The current view matrix.
     */
    glm::mat4 GetViewMatrix() const;

    /**
     * @brief Gets the projection matrix.
     * @return The current projection matrix.
     */
    glm::mat4 GetProjectionMatrix() const;

public:
    bool needCalculateViewMatrix;           ///< Flag indicating whether the view matrix needs to be recalculated.

private:
    glm::vec3 m_position;                   ///< The position of the camera.
    glm::vec3 m_target;                     ///< The target point the camera is looking at.
    glm::vec3 m_upVector;                   ///< The up vector of the camera.
    glm::mat4 m_viewMatrix;                 ///< The view matrix of the camera.
    glm::mat4 m_projectionMatrix;           ///< The projection matrix of the camera.

    OrthoFrustum m_frustum;                 ///< The orthographic frustum of the camera.
    std::string m_cameraType;               ///< The type of the camera.
};
