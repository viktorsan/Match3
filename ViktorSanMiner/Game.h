#pragma once
#ifndef __Game__
#define __Game__

#define WINDOW_SIZE_X 755
#define WINDOW_SIZE_Y 600
#define ELEMENTS 5
#define NUMBER_OF_TILES_W 8
#define NUMBER_OF_TILES_H 8
#define BOARD_SIZE_W 312
#define BOARD_SIZE_H 312
#define BOARD_X 344
#define BOARD_Y 114

#define CELL_SIZE_W (BOARD_SIZE_W/NUMBER_OF_TILES_W)
#define CELL_SIZE_H (BOARD_SIZE_H/NUMBER_OF_TILES_H)

#define GAME_TIME 60000
#define BONUS_TIME 2000
#define CELL_SCORE 20
#define CHANCE_OF_BONUS 50		//the higher the least

#include "SDL.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "ScreenFlow.h"
#include "Board.h"
#include "Cells.h"

struct Coords
{
	int x;
	int y;
};

class Game {

public:
	static Game* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	SDL_Renderer* getRenderer() const {return m_pRenderer;}

	bool init(const char* title, int xPos, int yPos, int height, int width, int flags);

	void render();
	void update();
	void handleEvent();
	void clean();
	void quit();

	void startPlay();
	void endPlay();

	void setScore(int score) {m_iScore = score;}
	int getScore() {return m_iScore;}

	bool running() {return m_bRunning;}

	GameObject* createGameObject(int x, int y, int value);

	Vector2D* convertScreenCoordToBoardCoords(Vector2D* screenCoords);

private:
	Game() {}
	~Game() {}

	void matchesManager();
	void intercambia(int x1, int y1, int x2, int y2);

	ScreenFlow* m_pScreenFlow;

	Board* m_Board;
	Cells* m_cells;

	static Game* s_pInstance;
	
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;

	int m_iScore;
};

typedef Game MyGame;

#endif