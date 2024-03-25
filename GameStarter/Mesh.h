#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include "Vertex.h"


class Mesh
{
public:
	Mesh();
	~Mesh();

	GLboolean LoadMesh(const std::string& filename);
	GLuint GetVBOId() const;
	GLuint GetIBOId() const;
	GLuint GetNumIndices() const;

public:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;

private:
	GLuint m_iVBO, m_iIBO;
	GLuint m_numIndices;
};