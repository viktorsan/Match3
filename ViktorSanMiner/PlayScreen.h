#pragma once
#include "gamescreen.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Cells.h"
#include "Board.h"
#include "Fuse.h"

class PlayScreen : public GameScreen
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getScreenID() const {return s_playID; }

private:
	static const std::string s_playID;

	GameObject* m_pBackground;
	GameObject* m_pSelected;

	Cells* m_pCells;
	Board* m_pBoard;

	Fuse* m_pFuse;

	Vector2D* firstCellSelected;
	Vector2D* secondCellSelected;

	Vector2D screenSelectedFirstCell;	//retain value of mouse movement in the button down moment

	bool inClick;		//filter the mouse button down
	bool changedBoard;	//true after every sucessful move

	Uint32 m_iTimeInit;	//time when the level started

	long double m_iScore;
	SDL_Color text_color;

	Vector2D* convertScreenCoordToBoardCoords(Vector2D* screenCoords);
	void intercambia(int x1, int y1, int x2, int y2);
	void removeCell(int x, int y);
	GameObject* createCell(int x, int y, int value);
	void matchesManager();

	void soundEffect();
};

