#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance = 0;

SoundManager::SoundManager(void)
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}


SoundManager::~SoundManager(void)
{
	Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string ID, sound_type type)
{
	if (type==SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());

		if (pMusic == 0)
		{
			return false;
		}

		m_music[ID] = pMusic;
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		if (pChunk == 0)
		{
			return false;
		}

		m_sfx[ID] = pChunk;
		return true;
	}
	return false;
}

void SoundManager::playMusic(std::string ID, int loop)
{
	Mix_PlayMusic(m_music[ID],loop);
}

void SoundManager::playSound(std::string ID, int loop)
{
	Mix_PlayChannel(-1,m_sfx[ID],loop);
}

void SoundManager::stopMusic()
{
	Mix_FadeOutMusic(1000);
}
