#include "Sprite2D.h"
#include "ResourceManager.h"
#include "IDGenerator.h"

Sprite2D::Sprite2D(const std::shared_ptr<Texture>& texture)
{
	m_objectId = getUniqueID();
	m_texture = texture;
	m_objectType = "sprite";
	m_mesh = ResourceManager::GetInstance()->GetMesh("quad_center.nfg");
}

Sprite2D::Sprite2D(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Texture> texture)
{
	m_objectId = getUniqueID();
	m_mesh = mesh;
	m_texture = texture;
	m_objectType = "sprite";
}

void Sprite2D::SendUniformData(std::map<std::string, GLint>& uniformLocationData)
{
}
