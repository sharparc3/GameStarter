#pragma once

#include <string>
#include <memory>

namespace SoLoud
{
	class Wav;
}

class Sound
{
public:
	Sound(const std::string& filename);
	~Sound();
	void LoadSound(const std::string& filename);
	void SetVolume(float volume);
	void SetLoop(bool loop);
	void Stop();
	float GetLength();


	friend class SoundPlayer;
private:
	std::shared_ptr<SoLoud::Wav> m_sound;

private:
	Sound();

};