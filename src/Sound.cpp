#include "Sound.h"

#include <iostream>
#include <soloud/soloud_wav.h>


Sound::Sound(const std::string& filename)
{
	m_sound = std::make_shared<SoLoud::Wav>();
	LoadSound(filename.c_str());
}

Sound::~Sound()
{
	m_sound = nullptr;
}

void Sound::LoadSound(const std::string& filename)
{
	SoLoud::result r = m_sound->load(filename.c_str());
	if (r != SoLoud::SO_NO_ERROR)
	{
		std::cout << "Failed to load sound: " << filename << "\n";
	}
}

void Sound::SetVolume(float volume)
{
	m_sound->setVolume(volume);
}

void Sound::SetLoop(bool loop)
{
	m_sound->setLooping(loop);
}

void Sound::Stop()
{
	m_sound->stop();
}

float Sound::GetLength()
{
	return static_cast<float>(m_sound->getLength());
}
