#include <glm/gtc/matrix_transform.hpp>
#include "BaseObject.h"


BaseObject::BaseObject(GLuint id, std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture) : 
	m_mesh(mesh), m_texture(texture), m_objectId(id)
{
	m_position = glm::vec3(0.f, 0.f, 0.f);
	m_rotationAngle = glm::vec3(0.f, 0.f, 0.f);
	m_scale = glm::vec3(0.f, 0.f, 0.f);
	m_worldMatrix = glm::mat4(1.f);
	m_needCalculateWorldMatrix = true;
}

BaseObject::~BaseObject()
{
	m_mesh = nullptr;
	m_texture = nullptr;
}

void BaseObject::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position = glm::vec3(x, y, z);
	m_needCalculateWorldMatrix = true;
}

void BaseObject::SetPosition(const glm::vec3& position)
{
	m_position = position;
	m_needCalculateWorldMatrix = true;
}

void BaseObject::SetRotation(const glm::vec3& rotation)
{
	m_rotationAngle = rotation;
	m_needCalculateWorldMatrix = true;
}

void BaseObject::SetRotation(GLfloat z, GLfloat x, GLfloat y)
{
	m_rotationAngle = glm::vec3(x, y, z);
	m_needCalculateWorldMatrix = true;
}

void BaseObject::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
	m_needCalculateWorldMatrix = true;
}

void BaseObject::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
	m_scale = glm::vec3(x, y, z);
	m_needCalculateWorldMatrix = true;
}

void BaseObject::RecalculateWorldMatrix()
{
	m_worldMatrix = glm::mat4(1.0f);
	m_worldMatrix = glm::translate(m_worldMatrix, m_position);
	m_worldMatrix = glm::rotate(m_worldMatrix, glm::radians(m_rotationAngle.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_worldMatrix = glm::rotate(m_worldMatrix, glm::radians(m_rotationAngle.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_worldMatrix = glm::rotate(m_worldMatrix, glm::radians(m_rotationAngle.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_worldMatrix = glm::scale(m_worldMatrix, m_scale);
	//glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), m_position);
	//glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_scale);
	//glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotationAngle.x), glm::vec3(1.0f, 0.0f, 0.0f));
	//glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotationAngle.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 rotationMatrixZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotationAngle.z), glm::vec3(0.0f, 0.0f, 1.0f));
	//glm::mat4 rotationMat = rotationMatrixZ * rotationMatrixY * rotationMatrixX;
	//m_worldMatrix = translationMat * rotationMat * scaleMat;

	m_needCalculateWorldMatrix = false;
}

void BaseObject::SendUniformData(std::map<std::string, GLint>& uniformLocationData)
{

}

glm::vec3 BaseObject::GetPosition() const
{
	return m_position;
}

glm::vec3 BaseObject::GetScale() const
{
	return m_scale;
}

glm::vec3 BaseObject::GetRotation() const
{
	return m_rotationAngle;
}

glm::mat4 BaseObject::GetWorldMatrix() const
{
	return m_worldMatrix;
}

GLuint BaseObject::GetID() const
{
	return m_objectId;
}
