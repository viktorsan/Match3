#pragma once
#ifndef __TextureManager__
#define __TextureManager__
#include <string>
#include <map>
#include "SDL.h"

class TextureManager {

private:
	TextureManager() {}
	~TextureManager() {}

	static TextureManager* s_pInstance;
	std::map<std::string, SDL_Texture*> m_textureMap;


public:
	static TextureManager* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw(std::string id, int x, int y, int w, int h, SDL_Renderer* pRenderer);

	void drawButton(std::string id, int x, int y, int w, int h, int state, SDL_Renderer* pRenderer);

	void clearFromTextureMap(std::string ID) { m_textureMap.erase(ID);}
};

typedef TextureManager MyTextureManager;

#endif