#include "Renderer.h"
#include "BaseObject.h"
#include "Camera.h"
#include "SpriteAnimation.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	m_RenderObjects.clear();
}

void Renderer::SetCamera(const std::shared_ptr<Camera>& camera)
{
	m_camera = camera;
}

void Renderer::AddObject(const std::shared_ptr<BaseObject>& object)
{
	m_RenderObjects[object->GetID()] = object;
}

void Renderer::RemoveObject(const std::shared_ptr<BaseObject>& object)
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

	for (auto& obj : m_RenderObjects)
	{
		if (obj.second->needMatrixCalc)
		{
			obj.second->RecalculateWorldMatrix();
		}

		// use shader
		GLint program = obj.second->m_shader->GetProgramID();
		//obj.second->m_shader->Use();
		glUseProgram(program);

		// bind VBO
		GLuint VBOid = obj.second->m_mesh->GetVBOId();
		glBindBuffer(GL_ARRAY_BUFFER, VBOid);

		// bind IBO
		GLuint IBOid = obj.second->m_mesh->GetIBOId();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOid);

		// bind texture
		GLuint textureID = obj.second->m_texture->GetTextureID();
		obj.second->m_texture->Bind();

		// bind VAO
		GLuint VAOid = obj.second->m_mesh->GetVAOId();
		glBindVertexArray(VAOid);

		// send uniform data
		auto uniformLocs = obj.second->m_shader->m_uniformLocations;
		if (uniformLocs["worldMatrix"] != -1)
		{
			// get the world matrix
			auto worldMatrix = obj.second->GetWorldMatrix();
			glUniformMatrix4fv(uniformLocs["worldMatrix"], 1, GL_FALSE, &worldMatrix[0][0]);
		}
		if (uniformLocs["viewMatrix"] != -1)
		{
			auto viewMatrix = m_camera->GetViewMatrix();
			glUniformMatrix4fv(uniformLocs["viewMatrix"], 1, GL_FALSE, &viewMatrix[0][0]);
		}
		if (uniformLocs["projectionMatrix"] != -1)
		{
			auto projectionMatrix = m_camera->GetProjectionMatrix();
			glUniformMatrix4fv(uniformLocs["projectionMatrix"], 1, GL_FALSE, &projectionMatrix[0][0]);
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
}

