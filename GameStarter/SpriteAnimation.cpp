#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(GLuint id, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, float frameTime, int frameCount) :
	BaseObject(id, mesh, shader, texture), m_frameCount(frameCount), m_secondBtFrame(frameTime)
{
	m_repeat = true;
	m_done = false;
	m_timeSinceLastFrame = 0.f;
	m_currentFrame = 0;
}

void SpriteAnimation::Update(GLfloat deltaTime)
{
	m_timeSinceLastFrame += deltaTime;
	if (m_timeSinceLastFrame >= m_secondBtFrame)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount && !m_repeat)
		{
			m_done = true;
		}
		m_currentFrame %= m_frameCount;
		m_timeSinceLastFrame = 0.f;
	}
}

void SpriteAnimation::SetRepeat(bool repeat)
{
	m_repeat = repeat;
}
