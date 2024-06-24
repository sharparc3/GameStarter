#pragma once

#include <string>
#include <memory>

namespace SoLoud
{
	class Wav;
}

/**
 * @class Sound
 * @brief Manages an audio sound.
 *
 * This class handles loading, playing, and managing properties of an audio sound.
 */
class Sound
{
public:
	/**
	 * @brief Deleted default constructor to prevent creating an uninitialized Sound object.
	 */
	Sound() = delete;

	/**
	 * @brief Constructs a Sound object and loads a sound from a file.
	 * @param filename The path to the sound file.
	 */
	Sound(const std::string& filename);


	/**
	 * @brief Destroys the Sound object and releases associated resources.
	 */
	~Sound();

	/**
	 * @brief Loads a sound from a file.
	 * @param filename The path to the sound file.
	 */
	void LoadSound(const std::string& filename);

	/**
	 * @brief Sets the volume of the sound.
	 * @param volume The volume level (0.0 to 1.0).
	 */
	void SetVolume(float volume);

	/**
	 * @brief Sets whether the sound should loop.
	 * @param loop True to enable looping, false to disable.
	 */
	void SetLoop(bool loop);


	/**
	 * @brief Stops the sound if it is playing.
	 */
	void Stop();

	/**
	 * @brief Gets the length of the sound in seconds.
	 * @return The length of the sound.
	 */
	float GetLength();

	friend class SoundPlayer;	///< Grants the SoundPlayer class access to Sound's private members.
private:
	std::shared_ptr<SoLoud::Wav> m_sound;	///< The sound object from the SoLoud library.
};