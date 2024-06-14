#include "Sprite2D.h"
#include "ResourceManager.h"

Sprite2D::Sprite2D(GLuint id, const std::shared_ptr<Texture>& texture)
{
	m_objectId = id;
	m_texture = texture;
	m_mesh = ResourceManager::GetInstance()->GetMesh("quad.nfg");
}

Sprite2D::Sprite2D(GLuint id, const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Texture> texture)
{
	m_objectId = id;
	m_mesh = mesh;
	m_texture = texture;
}

void Sprite2D::SendUniformData(std::map<std::string, GLint>& uniformLocationData)
{
}
