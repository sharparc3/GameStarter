#pragma once

#include <memory>
#include <vector>

#include "SingletonDclp.h"
#include "Config.h"

namespace SoLoud
{
	class Soloud;
}

class Sound;

/**
 * @class SoundPlayer
 * @brief Manages the playback of sound effects and music.
 *
 * This class implements the Singleton pattern to ensure only one instance is used throughout the application.
 */
class SoundPlayer : public SingletonDclp<SoundPlayer>
{
public:
	/**
	 * @brief Initializes the sound player.
	 */
	void Init();

	/**
	 * @brief Deinitializes the sound player and releases resources.
	 */
	void Deinit();

	/**
	 * @brief Plays a sound.
	 * @param sound A shared pointer to the sound to play.
	 * @return An unsigned integer handle to the playing sound.
	 * 
	 * Just ignore the handle if the sound doesn't need to be tuned after
	 */
	unsigned int Play(std::shared_ptr<Sound> sound);

	/**
	 * @brief Sets the volume of a playing sound.
	 * @param handle The handle of the playing sound.
	 * @param volume The volume level to set (0.0f to 1.0f).
	 */
	void SetVolume(int handle, float volume);

	/**
	 * @brief Pauses a playing sound.
	 * @param handle The handle of the playing sound.
	 */
	void Pause(unsigned int handle);

	/**
	 * @brief Resumes a paused sound.
	 * @param handle The handle of the paused sound.
	 */
	void Resume(unsigned int handle);

	/**
	 * @brief Stops a playing sound.
	 * @param handle The handle of the playing sound.
	 */
	void Stop(unsigned int handle);

	/**
	 * @brief Pauses all playing sounds.
	 */
	void PauseAll();

	/**
	 * @brief Stops all playing sounds.
	 */
	void StopAll();


	/**
	 * @brief Resumes all paused sounds.
	 */
	void ResumeAll();

private:
	std::shared_ptr<SoLoud::Soloud> m_SoloudPlayer;		///< The sound engine player.
	std::vector<int> m_handles;							///< Handles to currently playing sounds.
};

/**
 * @def SOUNDPLAYER
 * @brief Macro to get the singleton instance of the SoundPlayer.
 */
#define SOUNDPLAYER() SoundPlayer::GetInstance()