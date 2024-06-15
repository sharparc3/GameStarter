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
	~Renderer();
	void SetShader(const std::shared_ptr<Shader> shader);
	void SetCamera(const std::shared_ptr<Camera> camera);
	void AddObject(const std::shared_ptr<BaseObject> object);
	void RemoveObject(const std::shared_ptr<BaseObject> object);
	void RemoveObject(GLuint id);
	void ClearRenderer();
	void Render(bool frustumCulling = true);

private:
	std::map<GLuint, std::shared_ptr<BaseObject>> m_RenderObjects;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Shader> m_shader;
};