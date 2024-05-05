#pragma once

#include <memory>
#include <vector>

#include "SingletonDclp.h"
#include "Global.h"

namespace SoLoud
{
	class Soloud;
}

class Sound;

class SoundPlayer : public SingletonDclp<SoundPlayer>
{
public:
	void Init();
	void Deinit();
	unsigned int Play(std::shared_ptr<Sound> sound);
	void SetPlayerVolume(int handle, float volume);
	void Pause(unsigned int handle);
	void Resume(unsigned int handle);
	void Stop(unsigned int handle);
	void PauseAll();
	void StopAll();
	void ResumeAll();

private:
	std::shared_ptr<SoLoud::Soloud> m_SoloudPlayer;
	std::vector<int> m_handles;
};