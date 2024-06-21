#pragma once

#include <glad/glad.h>
#include <memory>
#include <map>

class BaseObject;
class Camera;
class Shader;

class Renderer
{
public:
	Renderer() = delete;
	Renderer(const std::shared_ptr<Camera> camera, const std::shared_ptr<Shader> shader);
	virtual ~Renderer();
	virtual void SetShader(const std::shared_ptr<Shader> shader);
	virtual void SetCamera(const std::shared_ptr<Camera> camera);
	virtual void AddObject(const std::shared_ptr<BaseObject> object);
	virtual void RemoveObject(const std::shared_ptr<BaseObject> object);
	virtual void RemoveObject(GLuint id);
	virtual void ClearRenderer();
	virtual void Render(bool frustumCulling = true);

protected:
	std::map<GLuint, std::shared_ptr<BaseObject>> m_RenderObjects;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Shader> m_shader;
};

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
};

