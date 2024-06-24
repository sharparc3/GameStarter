#pragma once
#include "BaseObject.h"

/**
 * @class SpriteAnimation
 * @brief Represents an animated sprite object.
 *
 * This class handles the representation and management of an animated sprite object.
 */
class SpriteAnimation : public BaseObject
{
public:
	/**
	 * @brief Constructs a SpriteAnimation object with the given texture, frame time, and frame count.
	 * @param texture The texture for the sprite animation.
	 * @param frameTime The time duration for each frame.
	 * @param frameCount The total number of frames in the animation.
	 */
	SpriteAnimation(const std::shared_ptr<Texture> texture, float frameTime, int frameCount);

	/**
	 * @brief Constructs a SpriteAnimation object with the given mesh, texture, frame time, and frame count.
	 * @param mesh The mesh for the sprite animation.
	 * @param texture The texture for the sprite animation.
	 * @param frameTime The time duration for each frame.
	 * @param frameCount The total number of frames in the animation.
	 */
	SpriteAnimation(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Texture> texture, float frameTime, int frameCount);

	/**
	 * @brief Gets the number of frames in the animation.
	 * @return The number of frames.
	 */
	inline GLuint GetNumFrames() const { return m_frameCount; }

	/**
	 * @brief Gets the index of the current frame in the animation.
	 * @return The current frame index.
	 */
	inline GLuint GetCurrentFrameIndex() const { return m_currentFrame; }

	/**
	 * @brief Updates the animation state based on the elapsed time.
	 * @param deltaTime The time elapsed since the last update.
	 */
	void Update(GLfloat deltaTime);

	/**
	 * @brief Sets whether the animation should repeat.
	 * @param repeat True to enable repeating, false to disable.
	 */
	void SetRepeat(bool repeat);

	/**
	 * @brief Checks if the animation is set to repeat.
	 * @return True if the animation repeats, false otherwise.
	 */
	inline bool IsRepeat() const { return m_repeat; }

	/**
	 * @brief Sends uniform data to the shader.
	 * @param uniformLocationData A map of uniform names and their locations.
	 */
	void SendUniformData(std::map<std::string, GLint>& uniformLocationData) override;

public:
	bool m_done;					///< Indicates if the animation is done.
	friend class Renderer;			///< Grants the Renderer class access to SpriteAnimation's private members.
	friend class BatchRenderer;		///< Grants the BatchRenderer class access to SpriteAnimation's private members.

private:
	GLuint m_frameCount;			///< The number of frames in the animation.
	GLuint m_currentFrame;			///< The current frame index.
	GLfloat m_secondBtFrame;		///< The time duration between frames.
	GLfloat m_timeSinceLastFrame;	///< The time elapsed since the last frame update.
	bool m_repeat;					///< Indicates if the animation should repeat.
};