#include "MouseManager.h"
#include "Game.h"

MouseManager* MouseManager::s_pInstance = NULL;

MouseManager::MouseManager(void)
{
	for (int i=0; i<3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}

	m_mousePosition = new Vector2D;
}

void MouseManager::update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			MyGame::Instance()->quit();
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				m_mouseButtonStates[LEFT] = true;
			}
			if (event.button.button == SDL_BUTTON_MIDDLE)
			{
				m_mouseButtonStates[MIDDLE] = true;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				m_mouseButtonStates[RIGHT] = true;
			}
		}

		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				m_mouseButtonStates[LEFT] = false;
			}
			if (event.button.button == SDL_BUTTON_MIDDLE)
			{
				m_mouseButtonStates[MIDDLE] = false;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				m_mouseButtonStates[RIGHT] = false;
			}
		}

		if (event.type == SDL_MOUSEMOTION)
		{
			m_mousePosition->setValue(event.motion.x,event.motion.y);
		}
	}
}

MouseManager::~MouseManager(void)
{
}