#include "TextManager.h"
#include "Game.h"

TextManager* TextManager::s_pInstance = 0;

void TextManager::drawText(std::string message, std::string fontFile, int fontSize, int x, int y, SDL_Color color)
{
	TTF_Font *font = NULL;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);

	SDL_Surface *surf = TTF_RenderText_Blended(font,message.c_str(),color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(MyGame::Instance()->getRenderer(), surf);

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	SDL_Rect srcRect;
	SDL_Rect dstRect;

	SDL_QueryTexture(texture,NULL,NULL,&srcRect.w,&srcRect.h);

	srcRect.x = 0;
	srcRect.y = 0;
	dstRect.w = srcRect.w;
	dstRect.h = srcRect.h;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopy(MyGame::Instance()->getRenderer(), texture, &srcRect, &dstRect);

	texture = NULL;
	delete texture;
}

TextManager::TextManager(void)
{
	TTF_Init();
}


TextManager::~TextManager(void)
{
	TTF_Quit();
}
