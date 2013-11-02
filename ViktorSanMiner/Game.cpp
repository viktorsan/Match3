#include "Game.h"
#include "MenuScreen.h"
#include "PlayScreen.h"
#include "GameOverScreen.h"
#include "MouseManager.h"

Game* Game::s_pInstance = NULL;
Uint32 timePlaying;

bool Game::init(const char* title, int xPos, int yPos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_pWindow = SDL_CreateWindow(title,xPos,yPos,height,width,flags);
		if (m_pWindow!=0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow,-1,0);
			if (m_pRenderer!=0)
			{
				SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
			}
			else	return false;
		}
		else	return false;
	}
	else	return false;

	m_pScreenFlow = new ScreenFlow();
	m_pScreenFlow->clean();
	m_pScreenFlow->changeScreen(new MenuScreen());

	m_bRunning = true;
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	m_pScreenFlow->render();
	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	m_pScreenFlow->update();
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvent()
{
	MyMouseManager::Instance()->update();
}

void Game::startPlay()
{
	m_pScreenFlow->changeScreen(new PlayScreen());
}

void Game::endPlay()
{
	m_pScreenFlow->changeScreen(new GameOverScreen());
}

void Game::quit()
{
	m_bRunning = false;
}