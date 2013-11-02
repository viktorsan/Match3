#include "TextureManager.h"
#include "SDL_image.h"

TextureManager* TextureManager::s_pInstance = NULL;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface==NULL)
	{
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture!=NULL)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void TextureManager::draw(std::string id, int x, int y, int w, int h, SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = dstRect.w = w;
	srcRect.h = dstRect.h = h;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopy(pRenderer, m_textureMap[id], NULL, &dstRect);
}

void TextureManager::drawButton(std::string id, int x, int y, int w, int h, int state, SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = 0 + w*state;
	srcRect.y = 0;
	srcRect.w = dstRect.w = w;
	srcRect.h = dstRect.h = h;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &dstRect);
}