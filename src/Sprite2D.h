#pragma once

#include "BaseObject.h"

/**
 * @class Sprite2D
 * @brief Represents a 2D sprite object.
 *
 * This class handles the representation and management of a 2D sprite object.
 */
class Sprite2D : public BaseObject
{
public:
    /**
     * @brief Deleted default constructor to prevent creating an uninitialized Sprite2D object.
     */
	Sprite2D() = delete;

    /**
     * @brief Constructs a Sprite2D object with the given texture.
     * @param texture The texture for the sprite.
     */
    Sprite2D(const std::shared_ptr<Texture>& texture);

    /**
     * @brief Constructs a Sprite2D object with the given mesh and texture.
     * @param mesh The mesh for the sprite.
     * @param texture The texture for the sprite.
     */
	Sprite2D(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Texture> texture);

    /**
     * @brief Sends uniform data to the shader.
     * @param uniformLocationData A map of uniform names and their locations.
     */
	void SendUniformData(std::map<std::string, GLint>& uniformLocationData) override;
};