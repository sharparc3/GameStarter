#pragma once

#include "BaseObject.h"

class Sprite2D : public BaseObject
{
public:
	//using BaseObject::BaseObject;
	Sprite2D() = delete;
    Sprite2D(const std::shared_ptr<Texture>& texture);
	Sprite2D(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Texture> texture);
	void SendUniformData(std::map<std::string, GLint>& uniformLocationData) override;
private:

};