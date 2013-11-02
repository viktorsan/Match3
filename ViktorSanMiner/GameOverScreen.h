#pragma once
#include "gamescreen.h"
#include "GameButton.h"
#include "GameObject.h"

class GameOverScreen :	public GameScreen
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getScreenID() const {return s_menuID;}

private:
	static const std::string s_menuID;

	long double m_iScore;

	GameObject* m_pBackground;
	GameButton* m_pButton1;
	GameButton* m_pButton2;

	//callbacks for the buttons
	static void s_menuToPlay();
	static void s_exitFromMenu();
};