#include "Sprite2D.h"

Sprite2D::Sprite2D(GLuint id, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Texture>& texture) :
	BaseObject(id, mesh, texture)
{

}

void Sprite2D::SendUniformData(std::map<std::string, GLint>& uniformLocationData)
{
}
