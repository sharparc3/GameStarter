#include "Sprite2D.h"

Sprite2D::Sprite2D(GLuint id, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) :
	BaseObject(id, mesh, shader, texture)
{

}