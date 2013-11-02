#pragma once
#include <string>
#include <map>
#include "SDL_ttf.h"
class TextManager
{
public:
	static TextManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	void drawText(std::string message, std::string fontFile, int fontSize, int x, int y, SDL_Color color);

private:

	static TextManager* s_pInstance;

	TextManager(void);
	~TextManager(void);
};

typedef TextManager MyTextManager;

