#pragma once

#include <glad/glad.h>
#include <memory>
#include <map>

class BaseObject;
class Camera;

class Renderer
{
public:
	Renderer();
	~Renderer();
	void SetCamera(const std::shared_ptr<Camera>& camera);
	void AddObject(const std::shared_ptr<BaseObject>& object);
	void RemoveObject(const std::shared_ptr<BaseObject>& object);
	void RemoveObject(GLuint id);
	void ClearRenderer();
	void Render();

private:
	std::map<GLuint, std::shared_ptr<BaseObject>> m_RenderObjects;
	std::shared_ptr<Camera> m_camera;
};