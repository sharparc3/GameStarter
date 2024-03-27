#include "Sprite2D.h"

Sprite2D::Sprite2D(GLuint id, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) :
	BaseObject(id, mesh, shader, texture)
{
	// set up VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->GetVBOId());
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Position attribute (location = 0)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Texture coordinate attribute (location = 1)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint Sprite2D::GetVAO()
{
	return m_VAO;
}
