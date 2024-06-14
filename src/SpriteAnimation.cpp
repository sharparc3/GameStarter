#include "SpriteAnimation.h"
#include "ResourceManager.h"

SpriteAnimation::SpriteAnimation(GLuint id, const std::shared_ptr<Texture> texture, float frameTime, int frameCount) :
	m_frameCount(frameCount), m_secondBtFrame(frameTime)
{
	m_objectId = id;
	m_texture = texture;
	m_mesh = ResourceManager::GetInstance()->GetMesh("quad.nfg");
	m_repeat = true;
	m_done = false;
	m_timeSinceLastFrame = 0.f;
	m_currentFrame = 0;
}

SpriteAnimation::SpriteAnimation(GLuint id, const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Texture> texture, float frameTime, int frameCount) :
	m_frameCount(frameCount), m_secondBtFrame(frameTime)
{
	m_objectId = id;
	m_texture = texture;
	m_currentFrame = 0;
	m_done = false;
	m_repeat = true;
	m_timeSinceLastFrame = 0.f;
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

void SpriteAnimation::SendUniformData(std::map<std::string, GLint>& uniformLocationData)
{
	if (uniformLocationData["currentFrame"] != -1)
	{
		glUniform1f(uniformLocationData["currentFrame"], static_cast<GLfloat>(this->GetCurrentFrameIndex()));
	}
	if (uniformLocationData["frameCount"] != -1)
	{
		glUniform1f(uniformLocationData["frameCount"], static_cast<GLfloat>(this->GetNumFrames()));
	}
}
