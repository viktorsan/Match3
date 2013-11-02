#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"

void GameObject::init(int x, int y, std::string textureID)
{
	m_x_now = m_x_end = x;
	m_y_now = m_y_end = y;
	m_textureID = textureID;

	m_bBonus = false;
}

void GameObject::draw()
{
	MyTextureManager::Instance()->draw(m_textureID,BOARD_X + (m_x_now),BOARD_Y + (m_y_now),CELL_SIZE_W,CELL_SIZE_H,Game::Instance()->getRenderer());
	if (m_bBonus)
		MyTextureManager::Instance()->draw("bonus",BOARD_X + (m_x_now),BOARD_Y + (m_y_now),CELL_SIZE_W,CELL_SIZE_H,Game::Instance()->getRenderer());
}

void GameObject::drawAtPos(int x, int y, int w, int h)
{
	MyTextureManager::Instance()->draw(m_textureID,x,y,w,h,MyGame::Instance()->getRenderer());
}

void GameObject::moveTo(int x, int y)
{
	m_x_end = x;
	m_y_end = y;
}

void GameObject::update()
{
	moving = false;

	if (m_y_now != m_y_end)
	{
		int moveY = (m_y_end - m_y_now)/4;
		if (!moveY) m_y_now = m_y_end;
		else {m_y_now += moveY;moving=true;} 
	}

	if (m_x_end != m_x_now)
	{
		int moveX = (m_x_end - m_x_now)/4;
		if (!moveX) m_x_now = m_x_end;
		else {m_x_now += moveX;moving=true;} 
	}
}

void GameObject::setValue(int value)
{
	m_value = value;
}

int GameObject::getValue()
{
	return m_value;
}

int GameObject::getActualX()
{
	return m_x_now;
}

int GameObject::getActualY()
{
	return m_y_now;
}