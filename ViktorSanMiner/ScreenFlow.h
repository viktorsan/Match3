#pragma once
#include "GameScreen.h"
#include <vector>

class ScreenFlow
{
public:
	ScreenFlow(void) {}
	~ScreenFlow(void) {}

	void pushScreen(GameScreen* pScreen);
	void changeScreen(GameScreen* pScreen);
	void popScreen();

	void update();
	void render();
	void clean();

private:

	std::vector<GameScreen*> m_gameScreens;
};

