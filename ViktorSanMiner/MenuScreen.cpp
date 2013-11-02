#include "MenuScreen.h"
#include "TextureManager.h"
#include "Game.h"


const std::string MenuScreen::s_menuID = "MENU";

void MenuScreen::update() 
{
	if (m_pButton2!=NULL) m_pButton2->update();
	if (m_pButton1!=NULL) m_pButton1->update();
}

void MenuScreen::render() 
{
	m_pBackground->drawAtPos(0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);
	m_pButton1->draw();
	m_pButton2->draw();
}

bool MenuScreen::onEnter() 
{
	if(!MyTextureManager::Instance()->load("resources/BackGroundMenu.jpg","background",MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/startGame.png","start",MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/exitGame.png","exit",MyGame::Instance()->getRenderer())) return false;

	m_pBackground = new GameObject();
	m_pBackground->init(0,0,"background");

	m_pButton1 = new GameButton("start",350,150,855,54,s_menuToPlay);
	m_pButton2 = new GameButton("exit",350,250,855,54,s_exitFromMenu);

	return true;
}

bool MenuScreen::onExit()
{
	MyTextureManager::Instance()->clearFromTextureMap("background");
	MyTextureManager::Instance()->clearFromTextureMap("restart");
	MyTextureManager::Instance()->clearFromTextureMap("exit");

	m_pBackground->clean();
	m_pButton1->clean();
	m_pButton2->clean();

	return true;
}

void MenuScreen::s_exitFromMenu()
{
	MyGame::Instance()->quit();
}

void MenuScreen::s_menuToPlay()
{
	MyGame::Instance()->startPlay();
}