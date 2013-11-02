#include "GameOverScreen.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "Game.h"
#include <string>


const std::string GameOverScreen::s_menuID = "GAMEOVER";

void GameOverScreen::update() 
{
	m_pButton2->update();
	m_pButton1->update();	
}

void GameOverScreen::render() 
{
	m_pBackground->drawAtPos(0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);
	m_pButton1->draw();
	m_pButton2->draw();

	SDL_Color texto = {255, 255, 255};
	std::string score = std::to_string(m_iScore);
	MyTextManager::Instance()->drawText(("Your score is: " + score),"resources/fonts/animeace_i.ttf",20,250,55,texto);
}

bool GameOverScreen::onEnter() 
{
	if(!MyTextureManager::Instance()->load("resources/BackGroundEnd.jpg","background",MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/restartGame.png","restart",MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/exitGame.png","exit",MyGame::Instance()->getRenderer())) return false;

	if(!MySoundManager::Instance()->load("resources/audio/boom.wav","boom",SOUND_SFX)) return false;
	MySoundManager::Instance()->playSound("boom",0);

	m_pBackground = new GameObject();
	m_pBackground->init(0,0,"background");

	m_pButton1 = new GameButton("restart",235,380,855,54,s_menuToPlay);
	m_pButton2 = new GameButton("exit",235,450,855,54,s_exitFromMenu);

	m_iScore = MyGame::Instance()->getScore();

	return true;
}

bool GameOverScreen::onExit()
{
	MyTextureManager::Instance()->clearFromTextureMap("background");
	MyTextureManager::Instance()->clearFromTextureMap("restart");
	MyTextureManager::Instance()->clearFromTextureMap("exit");

	MySoundManager::Instance()->clearFromSoundMap("boom");

	m_pBackground->clean();
	m_pButton1->clean();
	m_pButton2->clean();

	return true;
}

void GameOverScreen::s_exitFromMenu()
{
	MyGame::Instance()->quit();
}

void GameOverScreen::s_menuToPlay()
{
	MyGame::Instance()->startPlay();
}