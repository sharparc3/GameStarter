#include "Renderer.h"
#include "BaseObject.h"
#include "Camera.h"
#include "SpriteAnimation.h"
#include "Shader.h"

Renderer::Renderer()
{
}

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

void Renderer::Render()
{
	if (m_camera->needCalculateViewMatrix)
	{
		m_camera->CalculateViewMatrix();
	}

	// use shader
	glUseProgram(m_shader->GetProgramID());

	std::shared_ptr<Texture> lastTexture;

	for (auto& obj : m_RenderObjects)
	{
		if (obj.second->needMatrixCalc)
		{
			obj.second->RecalculateWorldMatrix();
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

		// send uniform data
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
		if (uniformLocs["currentFrame"] != -1)
		{
			auto anim = std::dynamic_pointer_cast<SpriteAnimation>(obj.second);
			glUniform1f(uniformLocs["currentFrame"], static_cast<GLfloat>(anim->GetCurrentFrameIndex()));
		}
		if (uniformLocs["frameCount"] != -1)
		{
			auto anim = std::dynamic_pointer_cast<SpriteAnimation>(obj.second);
			glUniform1f(uniformLocs["frameCount"], static_cast<GLfloat>(anim->GetNumFrames()));
		}

		// Draw	
		glDrawElements(GL_TRIANGLES, obj.second->m_mesh->GetNumIndices(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

