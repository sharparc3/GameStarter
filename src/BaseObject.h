#pragma once
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

/**
 * @class BaseObject
 * @brief Represents a basic object in the game with position, rotation, and scale.
 *
 * This class provides functionality to set and get the transformation properties of the object and recalculate its world matrix.
 */
class BaseObject
{
public:
	/**
	 * @brief Constructs a BaseObject with the given mesh and texture.
	 * @param mesh A shared pointer to the mesh of the object.
	 * @param texture A shared pointer to the texture of the object.
	 */
	BaseObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture);

	/**
	 * @brief Destroys the BaseObject.
	 */
	virtual ~BaseObject();

	/**
	 * @brief Sets the position of the object.
	 * @param x The x-coordinate of the position.
	 * @param y The y-coordinate of the position.
	 * @param z The z-coordinate of the position. Defaults to 0.
	 */
	void SetPosition(GLfloat x, GLfloat y, GLfloat z = 0.f);


	/**
	 * @brief Sets the position of the object.
	 * @param position A vector representing the position.
	 */
	void SetPosition(const glm::vec3& position);

	/**
	 * @brief Sets the rotation of the object.
	 * @param rotation A vector representing the rotation.
	 */
	void SetRotation(const glm::vec3& rotation);


	/**
	 * @brief Sets the rotation of the object.
	 * @param z The z-angle of the rotation.
	 * @param x The x-angle of the rotation. Defaults to 0.
	 * @param y The y-angle of the rotation. Defaults to 0.
	 */
	void SetRotation(GLfloat z, GLfloat x = 0.f, GLfloat y = 0.f);

	/**
	 * @brief Sets the scale of the object.
	 * @param scale A vector representing the scale.
	 */
	void SetSize(const glm::vec3& scale);

	/**
	 * @brief Sets the scale of the object.
	 * @param x The x-coordinate of the scale.
	 * @param y The y-coordinate of the scale.
	 * @param z The z-coordinate of the scale. Defaults to 1.0.
	 */
	void SetSize(GLfloat x, GLfloat y, GLfloat z = 1.0f);

	/**
	 * @brief Recalculates the 4x4 world matrix of the object.
	 */
	void RecalculateWorldMatrix();

	/**
	 * @brief Sends uniform data to the shader.
	 * @param uniformLocationData A map of uniform names to their location.
	 */
	virtual void SendUniformData(std::map<std::string, GLint>& uniformLocationData);

	/**
	 * @brief Gets the position of the object.
	 * @return A vector 3 representing the position.
	 */
	glm::vec3 GetPosition() const;

	/**
	 * @brief Gets the scale of the object.
	 * @return A vector 3 representing the scale.
	 */
	glm::vec3 GetScale() const;


	/**
	 * @brief Gets the rotation of the object.
	 * @return A vector 3 representing the rotation.
	 */
	glm::vec3 GetRotation() const;

	/**
	 * @brief Gets the world matrix of the object.
	 * @return The 4x4 world matrix.
	 */
	glm::mat4 GetWorldMatrix() const;

	/**
	 * @brief Gets the ID of the object.
	 * @return The object ID.
	 */
	GLuint GetID() const;

	bool m_needCalculateWorldMatrix;	///< Indicates if the world matrix needs to be recalculated.
	friend class Renderer;				///< Grants Renderer access to private members.
	friend class BatchRenderer;			///< Grants BatchRenderer access to private members.
protected:
	/**
	 * @brief Default constructor for BaseObject.
	 * 
	 * This constructor can only be accessed by derived classes for creating custom components.
	 */
	BaseObject();


	int m_objectId;							///< The unique ID of the object.
	glm::vec3 m_position;					///< The position of the object.
	glm::vec3 m_rotationAngle;				///< The rotation angle of the object.
	glm::vec3 m_scale;						///< The scale of the object.
	glm::mat4 m_worldMatrix;				///< The world matrix of the object.
	std::shared_ptr<Mesh> m_mesh;			///< The mesh of the object.
	std::shared_ptr<Texture> m_texture;		///< The texture of the object.
	std::string m_objectType;				///< The string name of the object.
};