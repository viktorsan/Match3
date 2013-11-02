#pragma once
#include <iostream>
#include <string>
#include <map>
#include "SDL_mixer.h"

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	static SoundManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string ID, sound_type type);

	void playSound(std::string ID, int loop);
	void playMusic(std::string ID, int loop);

	void stopMusic();

	void clearFromSoundMap(std::string ID) { m_sfx.erase(ID);}
	void clearFromMusicMap(std::string ID) { m_music.erase(ID);}

private:

	static SoundManager* s_pInstance;

	std::map<std::string, Mix_Chunk*> m_sfx;
	std::map<std::string, Mix_Music*> m_music;

	SoundManager(void);
	~SoundManager(void);

	SoundManager(const SoundManager&);
	SoundManager &operator=(const SoundManager&);
};

typedef SoundManager MySoundManager;