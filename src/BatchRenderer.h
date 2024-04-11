#pragma once
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>


class BaseObject;
class Camera;
class Shader;
class Texture;
struct Vertex;

class BatchRenderer
{
public:
	BatchRenderer();
	BatchRenderer(GLuint maxVerticesCount, const std::shared_ptr<Camera> camera, const std::shared_ptr<Shader> shader);
	~BatchRenderer();
	void SetCamera(const std::shared_ptr<Camera> camera);
	void SetShader(const std::shared_ptr<Shader> shader);
	void AddObject(const std::shared_ptr<BaseObject> obj);
	void RemoveObject(const std::shared_ptr<BaseObject> obj);
	void RemoveObject(GLuint id);
	void BuildBuffer();
	void Render();

private:
	void PushVertex(const Vertex& vertex);

private:
	// contains objects to be rendered. stored by pair id - object
	std::map<GLuint, std::shared_ptr<BaseObject>> m_RenderObjects;

	// big buffer for batching
	std::vector<Vertex> m_vertexBuffer;
	std::vector<GLuint> m_indexBuffer;
	std::vector<glm::mat4> m_uniformBuffer;

	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Texture> m_texture;
	GLuint m_maxVerticesCount;

	GLuint m_VBO, m_IBO, m_VAO;
	bool m_needRebuildBuffer;
	bool m_needSendData;
};