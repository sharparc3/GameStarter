#pragma once
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class BaseObject
{
public:
	BaseObject(GLuint id, std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture);
	virtual ~BaseObject();
	void SetPosition(GLfloat x, GLfloat y, GLfloat z = 0.f);
	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetRotation(GLfloat z, GLfloat x = 0.f, GLfloat y = 0.f);
	void SetScale(const glm::vec3& scale);
	void SetScale(GLfloat x, GLfloat y, GLfloat z = 1.0f);
	void RecalculateWorldMatrix();

	glm::vec3 GetPosition() const;
	glm::vec3 GetScale() const;
	glm::vec3 GetRotation() const;
	glm::mat4 GetWorldMatrix() const;
	GLuint GetID() const;

	bool m_needCalculateWorldMatrix;
	friend class Renderer;
	friend class BatchRenderer;
protected:
	GLuint m_objectId;

	glm::vec3 m_position;
	glm::vec3 m_rotationAngle;
	glm::vec3 m_scale;
	glm::mat4 m_worldMatrix;
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Texture> m_texture;
};