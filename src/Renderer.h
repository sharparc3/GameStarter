#pragma once

#include <glad/glad.h>
#include <memory>
#include <string>
#include <queue>

class BaseObject;
class Camera;
class Shader;

/**
 * @class Renderer
 * @brief Manages and renders graphic objects in the game.
 *
 * This class handles the addition, removal, and rendering of game objects, utilizing a camera and shader for rendering.
 */
class Renderer
{
public:
	/**
	 * @brief Constructs a Renderer with the given camera and shader.
	 * @param camera A shared pointer to the camera.
	 * @param shader A shared pointer to the shader.
	 */
	Renderer(const std::shared_ptr<Camera> camera, const std::shared_ptr<Shader> shader);

	/**
	 * @brief Called when free the Renderer.
	 */
	virtual ~Renderer();

	/**
	 * @brief Sets the shader for rendering.
	 * @param shader A shared pointer to the shader.
	 */
	virtual void SetShader(const std::shared_ptr<Shader> shader);

	/**
	 * @brief Sets the camera for rendering.
	 * @param camera A shared pointer to the camera.
	 */
	virtual void SetCamera(const std::shared_ptr<Camera> camera);

	/**
	 * @brief Adds an object to the renderer.
	 * @param object A shared pointer to the object.
	 */
	virtual void AddObject(const std::shared_ptr<BaseObject> object);

	/**
	 * @brief Removes an object from the renderer.
	 * @param object A shared pointer to the object.
	 */
	virtual void RemoveObject(const std::shared_ptr<BaseObject> object);

	/**
	 * @brief Removes an object from the renderer by its ID.
	 * @param id The ID of the object.
	 */
	virtual void RemoveObject(GLuint id);

	/**
	 * @brief Clears all objects from the renderer.
	 */
	virtual void ClearRenderer();

	/**
	 * @brief Renders the objects. This must be called in the Draw() method of the state.
	 * @param frustumCulling Enables frustum culling if true.
	 */
	virtual void Render(bool frustumCulling = true);

	const std::string& GetRendererType() const
	{
		return m_rendererType;
	}

protected:
	/**
	 * @brief Default constructor for custom renderer.
	 */
	Renderer();
	std::queue<std::shared_ptr<BaseObject>> m_RenderObjects;		///< Map of objects to render, keyed by their ID.
	std::shared_ptr<Camera> m_camera;									///< The camera used for rendering.
	std::shared_ptr<Shader> m_shader;									///< The shader used for rendering.
	std::string m_rendererType;
};


/**
 * @class SpriteRenderer
 * @brief Specialized renderer for sprites.
 *
 * Inherits from Renderer and provides functionality specific to rendering sprites.
 * This can be used to render both Sprite2D and Text because 
 * Text is just a Sprite2D with text texture
 */
class SpriteRenderer : public Renderer
{
public:
	/**
	 * @brief Constructs a SpriteRenderer.
	 */
	SpriteRenderer();
};


/**
 * @class AnimationRenderer
 * @brief Specialized renderer for animations.
 *
 * Inherits from Renderer and provides functionality specific to rendering animations.
 */
class AnimationRenderer : public Renderer
{
public:
	/**
	 * @brief Constructs an AnimationRenderer.
	 */
	AnimationRenderer();
};

