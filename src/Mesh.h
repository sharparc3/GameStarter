#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include "Vertex.h"

/**
 * @class Mesh
 * @brief Represents a 3D mesh composed of vertices and indices.
 *
 * This class handles loading, storing, and managing 3D mesh data, 
 * including generating OpenGL buffers.
 */
class Mesh
{
public:
	/**
	 * @brief Constructs an empty Mesh object.
	 */
	Mesh();

	/**
	 * @brief Destroys the Mesh object and frees associated resources.
	 */
	~Mesh();

	/**
	 * @brief Constructs a Mesh object with the given vertices and indices.
	 * @param vertices The vertices of the mesh.
	 * @param indices The indices of the mesh.
	 */
	Mesh(std::vector<Vertex>&& vertices, std::vector<GLuint>&& indices);

	/**
	 * @brief Copy constructor for Mesh.
	 * @param other The Mesh object to copy from.
	 */
	Mesh(const Mesh& other);

	/**
	 * @brief Loads a mesh from a file.
	 * @param filename The path to the mesh file.
	 * @return True if the mesh was loaded successfully, false otherwise.
	 */
	GLboolean LoadMesh(const std::string& filename);

	/**
	 * @brief Gets the Vertex Buffer Object (VBO) ID. Mostly unused. Left over from old design.
	 * @return The VBO ID.
	 */
	GLuint GetVBOId() const;

	/**
	 * @brief Gets the Index Buffer Object (IBO) ID. Mostly unused. Left over from old design.
	 * @return The IBO ID.
	 */
	GLuint GetIBOId() const;

	/**
	 * @brief Gets the Vertex Array Object (VAO) ID.
	 * @return The VAO ID.
	 */
	GLuint GetVAOId() const;

	/**
	 * @brief Gets the number of indices in the mesh.
	 * @return The number of indices.
	 */
	GLuint GetNumIndices() const;

public:
	std::vector<Vertex> m_vertices; ///< The vertices of the mesh.
	std::vector<GLuint> m_indices;  ///< The indices of the mesh.

private:
	GLuint m_iVBO;			///< The Vertex Buffer Object (VBO) ID.
	GLuint m_iIBO;			///< The Index Buffer Object (IBO) ID.
	GLuint m_iVAO;			///< The Vertex Array Object (VAO) ID.
	GLuint m_numIndices;	///< The number of indices in the mesh.

	/**
	 * @brief Generates OpenGL buffers for the mesh from defined data.
	 * @param freeOld Indicates whether to free old buffers if they exist.
	 */
	void GenerateGLBuffer(bool freeOld = false);
};