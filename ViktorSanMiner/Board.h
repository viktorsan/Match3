#pragma once
#include "Vector2D.h"
#include <vector>

class Board
{
private:
	int* m_logicBoard;
	
	int m_iSize_w;
	int m_iSize_h;

	int m_iElements;

	bool nextMove();

public:
	Board(int size_x, int size_y, int elements);
	~Board() {}

	void setCell(int x, int y, int value);
	int getCell(int x, int y);
	bool findMatch(int startX, int startY);

	std::vector<Vector2D> returnMatch(int startX, int startY);

	std::vector<Vector2D> returnAllMatches();

	void removeCell(int x, int y);

};

