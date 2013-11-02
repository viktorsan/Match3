#include "GameButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "MouseManager.h"


GameButton::GameButton(std::string ID, int x, int y, int w, int h, void (*callback) ()) : m_callback(callback)
{
	m_x = x;
	m_y = y;
	m_w = w/3;
	m_h = h;
	m_textureID = ID;
	m_currentState = MOUSE_OUT;
}

void GameButton::draw()
{
	MyTextureManager::Instance()->drawButton(m_textureID,m_x,m_y,m_w,m_h,m_currentState,MyGame::Instance()->getRenderer());
}

void GameButton::update()
{
	Vector2D* pMousePos = MyMouseManager::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_x + m_w) &&
		pMousePos->getX() > m_x &&
		pMousePos->getY() < (m_y + m_h) &&
		pMousePos->getY() > m_y)
	{
		if (MyMouseManager::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentState = CLICKED;
			m_bReleased = false;
			m_callback();
		} else if (!MyMouseManager::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentState = MOUSE_OVER;
		}
	}
	else
	{
		m_currentState = MOUSE_OUT;
	}

	pMousePos = NULL;
	delete pMousePos;
}


GameButton::~GameButton(void)
{
}
