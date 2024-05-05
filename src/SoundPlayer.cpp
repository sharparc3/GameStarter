#include "SoundPlayer.h"

#include <iostream>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

#include "Sound.h"

void SoundPlayer::Init()
{
    m_SoloudPlayer = std::make_shared<SoLoud::Soloud>();
#if defined(WITH_SDL2_STATIC)
    int result = m_SoloudPlayer->init(SoLoud::Soloud::CLIP_ROUNDOFF, SoLoud::Soloud::SDL2);
    if (result != SoLoud::SO_NO_ERROR)
    {
        std::cerr << "Failed to initialize SoLoud with SDL2 backend." << std::endl;
    }
#else
    int result = m_SoloudPlayer->init();
    if (result != SoLoud::SO_NO_ERROR)
    {
        std::cerr << "Failed to initialize SoLoud." << std::endl;
    }
#endif
}

void SoundPlayer::Deinit()
{
    m_SoloudPlayer->deinit();
    m_SoloudPlayer = nullptr;
}

unsigned int SoundPlayer::Play(std::shared_ptr<Sound> sound)
{
    if (!sound)
    {
        return 0;
    }
    unsigned int handle = m_SoloudPlayer->play(*(sound->m_sound.get()));
    m_handles.push_back(handle);
    return handle;
}

void SoundPlayer::SetPlayerVolume(int handle, float volume)
{
    m_SoloudPlayer->setVolume(handle, volume);
}

void SoundPlayer::Pause(unsigned int handle)
{
    m_SoloudPlayer->setPause(handle, true);
}

void SoundPlayer::Resume(unsigned int handle)
{
    m_SoloudPlayer->setPause(handle, false);
}

void SoundPlayer::Stop(unsigned int handle)
{
    m_SoloudPlayer->stop(handle);
}

void SoundPlayer::PauseAll()
{
    m_SoloudPlayer->setPauseAll(true);
}

void SoundPlayer::StopAll()
{
    m_SoloudPlayer->stopAll();
}

void SoundPlayer::ResumeAll()
{
    m_SoloudPlayer->setPauseAll(false);
}

