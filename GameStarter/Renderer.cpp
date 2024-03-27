#include "Renderer.h"

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
	auto viewMatrix = m_camera->GetViewMatrix();
	auto projectionMatrix = m_camera->GetProjectionMatrix();

	for (auto& obj : m_RenderObjects)
	{
		if (obj.second->needMatrixCalc)
		{
			obj.second->RecalculateWorldMatrix();
		}

		// use shader
		GLint program = obj.second->m_shader->GetProgramID();
		glUseProgram(program);
		//obj.second->m_shader->Use();
		// bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, obj.second->m_mesh->GetVBOId());
		// bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.second->m_mesh->GetIBOId());
		// bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, obj.second->m_texture->GetTextureID());
		//obj.second->m_texture->Bind();
		// bind VAO
		//glBindVertexArray(obj.second->GetVAO());

		// get the world matrix
		auto worldMatrix = obj.second->GetWorldMatrix();

		// get uniform location
		GLint worldLoc = glGetUniformLocation(program, "worldMatrix");
		GLint viewLoc = glGetUniformLocation(program, "viewMatrix");
		GLint projectionLoc = glGetUniformLocation(program, "projectionMatrix");
		GLint wvpLoc = glGetUniformLocation(program, "wvpMatrix");

		auto wvp = projectionMatrix * viewMatrix * worldMatrix;

		// send matrix data
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, &worldMatrix[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(wvpLoc, 1, GL_FALSE, &wvp[0][0]);

		std::cout << "WVP Matrix:\n";
		for (int col = 0; col < 4; ++col) 
		{
			for (int row = 0; row < 4; ++row) 
			{
				std::cout << wvp[col][row] << " ";
			}
			std::cout << std::endl;
		}
		// Draw	
		glDrawElements(GL_TRIANGLES, obj.second->m_mesh->GetNumIndices(), GL_UNSIGNED_INT, 0);
	}
}
