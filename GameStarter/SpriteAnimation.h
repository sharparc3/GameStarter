#pragma once
#include "BaseObject.h"

class SpriteAnimation : public BaseObject
{
public:
	SpriteAnimation(GLuint id, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, float frameTime, int frameCount);
	inline GLuint GetNumFrames() const { return m_frameCount; }
	inline GLuint GetCurrentFrameIndex() const { return m_currentFrame; }
	void Update(GLfloat deltaTime);
	void SetRepeat(bool repeat);
	inline bool IsRepeat() const { return m_repeat; }
public:
	bool m_done;

private:
	GLuint m_frameCount, m_currentFrame;
	GLfloat m_secondBtFrame, m_timeSinceLastFrame;
	bool m_repeat;

};