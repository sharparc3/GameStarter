#include "BatchRenderer.h"

#include "Vertex.h"
#include "BaseObject.h"
#include "Shader.h"
#include "Camera.h"
#include "SpriteAnimation.h"

BatchRenderer::BatchRenderer()
{
	m_VBO = 0;
	m_IBO = 0;
	m_VAO = 0;
	m_maxVerticesCount = 0;
}

BatchRenderer::BatchRenderer(GLuint maxVerticesCount, const std::shared_ptr<Camera> camera, const std::shared_ptr<Shader> shader) :
	m_maxVerticesCount(maxVerticesCount), m_camera(camera), m_shader(shader)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_maxVerticesCount, NULL, GL_DYNAMIC_DRAW);

	// Position attribute (location = 0)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// Texture coordinate attribute (location = 1)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_maxVerticesCount * 4, NULL, GL_DYNAMIC_DRAW);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

BatchRenderer::~BatchRenderer()
{
}

void BatchRenderer::SetCamera(const std::shared_ptr<Camera> camera)
{
	m_camera = camera;
}

void BatchRenderer::SetShader(const std::shared_ptr<Shader> shader)
{
	m_shader = shader;
}

void BatchRenderer::AddObject(const std::shared_ptr<BaseObject> obj)
{
	GLuint id = obj->GetID();
	m_RenderObjects.insert(std::make_pair(id, obj));
}

void BatchRenderer::RemoveObject(const std::shared_ptr<BaseObject> obj)
{
	GLuint id = obj->GetID();
	m_RenderObjects.erase(id);
}

void BatchRenderer::RemoveObject(GLuint id)
{
	m_RenderObjects.erase(id);
}

void BatchRenderer::Render()
{
	if (!m_shader || !m_camera)
	{
		std::cout << "ERROR: invalid shader or camera";
		return;
	}

	int vertexCount = 0;
	glm::mat4 viewMatrix = m_camera->GetViewMatrix();
	glm::mat4 projectionMatrix = m_camera->GetProjectionMatrix();

	m_lastTexture = m_RenderObjects.begin()->second->m_texture;

	for (const auto& obj : m_RenderObjects)
	{
		// when buffer limit reaches -> draw then flush buffer
		if (m_vertexBuffer.size() + 4 > m_maxVerticesCount)
		{
			FlushBuffer();
		}
		// when texture change -> draw then change texture
		if (m_lastTexture != obj.second->m_texture)
		{
			FlushBuffer();
			m_lastTexture = obj.second->m_texture;
		}

		if (obj.second->needMatrixCalc)
		{
			obj.second->RecalculateWorldMatrix();
		}

		// push indices to index buffer
		auto& indicesData = obj.second->m_mesh->m_indices;
		for (int i = 0; i < indicesData.size(); i++)
		{
			m_indexBuffer.push_back(vertexCount + indicesData[i]);
		}

		// push vertices to vertex buffer
		auto& objVertexData = obj.second->m_mesh->m_vertices;
		glm::mat4 objModelMat = obj.second->GetWorldMatrix();
		glm::mat4 mvp;
		Vertex tempVertex;
		// calculate mvp matrix
		mvp = projectionMatrix * viewMatrix * objModelMat;
		for (int i = 0; i < objVertexData.size(); i++)
		{
			// perform vertex transformation on CPU
			tempVertex = objVertexData[i];
			glm::vec4 vertexPosition = glm::vec4(tempVertex.position, 1.0f);
			vertexPosition = mvp * vertexPosition;
			tempVertex.position = glm::vec3(vertexPosition.x, vertexPosition.y, vertexPosition.z);
			m_vertexBuffer.push_back(tempVertex);
			vertexCount++;
		}
	}
	FlushBuffer();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BatchRenderer::FlushBuffer()
{
	// use shader
	glUseProgram(m_shader->GetProgramID());

	// setup VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(m_vertexBuffer.size() * sizeof(Vertex)), m_vertexBuffer.data());
	
	// setup IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(m_indexBuffer.size() * sizeof(GLuint)), m_indexBuffer.data());

	// bind texture
	m_lastTexture->Bind();

	// bind VAO
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexBuffer.size()), GL_UNSIGNED_INT, 0);

	// flush buffers
	m_vertexBuffer.clear();
	m_indexBuffer.clear();
}

void BatchRenderer::PushVertex(const Vertex& vertex)
{
	m_vertexBuffer.push_back(vertex);
}
