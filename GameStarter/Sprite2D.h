#pragma once

#include "BaseObject.h"

class Sprite2D : public BaseObject
{
public:
	//using BaseObject::BaseObject;
    Sprite2D(GLuint id, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture);
	GLuint GetVAO() override;

private:

};