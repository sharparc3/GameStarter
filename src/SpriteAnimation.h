#pragma once
#include "BaseObject.h"

class SpriteAnimation : public BaseObject
{
public:
	SpriteAnimation(const std::shared_ptr<Texture> texture, float frameTime, int frameCount);
	SpriteAnimation(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Texture> texture, float frameTime, int frameCount);
	inline GLuint GetNumFrames() const { return m_frameCount; }
	inline GLuint GetCurrentFrameIndex() const { return m_currentFrame; }
	void Update(GLfloat deltaTime);
	void SetRepeat(bool repeat);
	inline bool IsRepeat() const { return m_repeat; }
	void SendUniformData(std::map<std::string, GLint>& uniformLocationData) override;

public:
	bool m_done;
	friend class Renderer;
	friend class BatchRenderer;

private:
	GLuint m_frameCount, m_currentFrame;
	GLfloat m_secondBtFrame, m_timeSinceLastFrame;
	bool m_repeat;

};