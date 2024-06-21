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
}

Renderer::~Renderer()
{
	m_RenderObjects.clear();
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
	m_RenderObjects[object->GetID()] = object;
}

void Renderer::RemoveObject(const std::shared_ptr<BaseObject> object)
{
	m_RenderObjects.erase(object->GetID());
}

void Renderer::RemoveObject(GLuint id)
{
	m_RenderObjects.erase(id);
}

void Renderer::ClearRenderer()
{
	m_RenderObjects.clear();
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

	for (auto& obj : m_RenderObjects)
	{
		if (obj.second->m_needCalculateWorldMatrix)
		{
			obj.second->RecalculateWorldMatrix();
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

			bool isVisible = isObjectVisible(obj.second->GetPosition(), obj.second->GetScale());
			if (!isVisible)
			{
				//LogInfo("Culled object with id: %d", obj.second->GetID());
				continue;
			}
		}

		// bind VAO
		GLuint VAOid = obj.second->m_mesh->GetVAOId();
		glBindVertexArray(VAOid);

		// bind VBO
		//GLuint VBOid = obj.second->m_mesh->GetVBOId();
		//glBindBuffer(GL_ARRAY_BUFFER, VBOid);

		// bind IBO
		GLuint IBOid = obj.second->m_mesh->GetIBOId();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOid);

		if (lastTexture != obj.second->m_texture)
		{
			// bind texture
			obj.second->m_texture->Bind();
		}

		// send WVP matrix uniform data
		auto uniformLocs = m_shader->m_uniformLocations;
		if (uniformLocs["u_mvpMatrix"] != -1)
		{
			// get the world matrix
			auto worldMatrix = obj.second->GetWorldMatrix();
			auto viewMatrix = m_camera->GetViewMatrix();
			auto projectionMatrix = m_camera->GetProjectionMatrix();
			worldMatrix = projectionMatrix * viewMatrix * worldMatrix;
			glUniformMatrix4fv(uniformLocs["u_mvpMatrix"], 1, GL_FALSE, &worldMatrix[0][0]);
		}

		// let object send other uniform data
		obj.second->SendUniformData(uniformLocs);

		// Draw	
		glDrawElements(GL_TRIANGLES, obj.second->m_mesh->GetNumIndices(), GL_UNSIGNED_INT, 0);
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
}

AnimationRenderer::AnimationRenderer()
{
	m_camera = std::make_shared<Camera>();
	m_camera->SetOrthographicProjection(0.f, (float)GAME()->GetWindowWidth(), 0.f, (float)GAME()->GetWindowHeight());
	m_shader = RESOURCE()->GetShader("animation");
}
