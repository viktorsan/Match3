#include "ScreenFlow.h"

void ScreenFlow::pushScreen(GameScreen* pScreen)
{
	m_gameScreens.push_back(pScreen);
	m_gameScreens.back()->onEnter();
}

void ScreenFlow::popScreen()
{
	if (!m_gameScreens.empty())
	{
		if (m_gameScreens.back()->onExit())
		{
			delete m_gameScreens.back();
			m_gameScreens.pop_back();
		}
	}
}

void ScreenFlow::changeScreen(GameScreen* pScreen)
{
	if (!m_gameScreens.empty())
	{
		if (m_gameScreens.back()->getScreenID() == pScreen->getScreenID()) return;

		if (m_gameScreens.back()->onExit())
		{
			delete m_gameScreens.back();
			m_gameScreens.pop_back();
		}
	}

	m_gameScreens.push_back(pScreen);
	m_gameScreens.back()->onEnter();
}

void ScreenFlow::update()
{
	if (!m_gameScreens.empty())
	{
		m_gameScreens.back()->update();
	}
}

void ScreenFlow::render()
{
	if (!m_gameScreens.empty())
	{
		m_gameScreens.back()->render();
	}
}

void ScreenFlow::clean()
{
    if(!m_gameScreens.empty())
    {
        m_gameScreens.back()->onExit();

        delete m_gameScreens.back();
        
        m_gameScreens.clear();
    }
}