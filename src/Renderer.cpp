#include "Renderer.h"
#include "BaseObject.h"
#include "Camera.h"
#include "SpriteAnimation.h"
#include "Shader.h"
#include "Logger.h"
#include "Game.h"
#include "ResourceManager.h"

Renderer::Renderer(const std::shared_ptr<Camera> camera, const std::shared_ptr<Shader> shader) : 
	m_camera(camera), m_shader(shader)
{
	m_rendererType = "renderer";
}

Renderer::~Renderer()
{
	ClearRenderer();
}

void Renderer::SetShader(const std::shared_ptr<Shader> shader)
{
	m_shader = shader;
}

void Renderer::SetCamera(const std::shared_ptr<Camera> camera)
{
	m_camera = camera;
}

void Renderer::AddObject(const std::shared_ptr<BaseObject> object)
{
	m_RenderObjects.push(object);
}

void Renderer::RemoveObject(const std::shared_ptr<BaseObject> object)
{
	std::queue<std::shared_ptr<BaseObject>> newQueue;

	while (!m_RenderObjects.empty()) 
	{
		auto& currentObject = m_RenderObjects.front();
		m_RenderObjects.pop();
		if (currentObject != object) 
		{
			newQueue.push(currentObject);
}
	}

	std::swap(m_RenderObjects, newQueue);
}

void Renderer::RemoveObject(GLuint id)
{
	std::queue<std::shared_ptr<BaseObject>> newQueue;

	while (!m_RenderObjects.empty()) 
	{
		auto& currentObject = m_RenderObjects.front();
		m_RenderObjects.pop();
		if (currentObject->GetID() != id)
		{
			newQueue.push(currentObject);
}
	}

	std::swap(m_RenderObjects, newQueue);
}

void Renderer::ClearRenderer()
{
	std::queue<std::shared_ptr<BaseObject>> empty;
	std::swap(m_RenderObjects, empty);
}

void Renderer::Render(bool frustumCulling)
{
	if (m_camera->needCalculateViewMatrix)
	{
		m_camera->CalculateViewMatrix();
	}

	// use shader
	glUseProgram(m_shader->GetProgramID());

	std::shared_ptr<Texture> lastTexture;

	OrthoFrustum cameraFrustum = m_camera->GetCameraFrustum();

	while (!m_RenderObjects.empty())
	{
		auto& obj = m_RenderObjects.front();
		m_RenderObjects.pop();
		if (obj->m_needCalculateWorldMatrix)
		{
			obj->RecalculateWorldMatrix();
		}

		if (frustumCulling)
		{
			auto isObjectVisible = [&cameraFrustum](const glm::vec3& pos, const glm::vec3& size) -> bool {
				// Calculate object's bounds
				glm::vec3 objectMin = pos;
				glm::vec3 objectMax = pos + size;

				// Check for intersection with the frustum
				bool isVisible = (objectMax.x >= cameraFrustum.left && objectMin.x <= cameraFrustum.right) &&
					(objectMax.y >= cameraFrustum.top && objectMin.y <= cameraFrustum.bottom) &&
					(objectMax.z >= cameraFrustum.near && objectMin.z <= cameraFrustum.far);

				return isVisible;
				};

			bool isVisible = isObjectVisible(obj->GetPosition(), obj->GetScale());
			if (!isVisible)
			{
				//LogInfo("Culled object with id: %d", obj.second->GetID());
				continue;
			}
		}

		// bind VAO
		GLuint VAOid = obj->m_mesh->GetVAOId();
		glBindVertexArray(VAOid);

		if (lastTexture != obj->m_texture)
		{
			// bind texture
			obj->m_texture->Bind();
		}

		// send WVP matrix uniform data
		auto uniformLocs = m_shader->m_uniformLocations;
		if (uniformLocs["u_mvpMatrix"] != -1)
		{
			// get the world matrix
			// and perform calculating MVP matrix on CPU side
			auto worldMatrix = obj->GetWorldMatrix();
			auto viewMatrix = m_camera->GetViewMatrix();
			auto projectionMatrix = m_camera->GetProjectionMatrix();
			worldMatrix = projectionMatrix * viewMatrix * worldMatrix;
			glUniformMatrix4fv(uniformLocs["u_mvpMatrix"], 1, GL_FALSE, &worldMatrix[0][0]);
		}

		// let object send other uniform data
		obj->SendUniformData(uniformLocs);

		// Draw	
		glDrawElements(GL_TRIANGLES, obj->m_mesh->GetNumIndices(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Renderer::Renderer()
{
}

SpriteRenderer::SpriteRenderer()
{
	m_camera = std::make_shared<Camera>();
	m_camera->SetOrthographicProjection(0.f, (float)GAME()->GetWindowWidth(), 0.f, (float)GAME()->GetWindowHeight());
	m_shader = RESOURCE()->GetShader("quad");
	m_rendererType = "sprite_renderer";
}

AnimationRenderer::AnimationRenderer()
{
	m_camera = std::make_shared<Camera>();
	m_camera->SetOrthographicProjection(0.f, (float)GAME()->GetWindowWidth(), 0.f, (float)GAME()->GetWindowHeight());
	m_shader = RESOURCE()->GetShader("animation");
	m_rendererType = "animation_renderer";
}
