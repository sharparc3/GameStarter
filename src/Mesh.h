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

	Mesh(std::vector<Vertex>&& vertices, std::vector<GLuint>&& indices);

	// copy contructor
	Mesh(const Mesh& other);

	GLboolean LoadMesh(const std::string& filename);
	GLuint GetVBOId() const;
	GLuint GetIBOId() const;
	GLuint GetVAOId() const;
	GLuint GetNumIndices() const;

public:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;

private:
	GLuint m_iVBO, m_iIBO, m_iVAO;
	GLuint m_numIndices;

	void GenerateGLBuffer(bool freeOld = false);
};