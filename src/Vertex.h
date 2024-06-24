#pragma once

#include <glm/glm.hpp>

/**
* @struct Vertex
* @brief Represents the most basic unit in OpenGL geometric data.
*/
struct Vertex
{
	glm::vec3 position;
	glm::vec2 uv;
};