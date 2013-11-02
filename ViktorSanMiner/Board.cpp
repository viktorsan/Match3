#include "Board.h"
#include <time.h>

Board::Board(int size_w, int size_h, int elements)
{
	m_iSize_w = size_w;
	m_iSize_h = size_h;
	m_iElements = elements;
	m_logicBoard = new int[size_w*size_h];
	
	srand(time(NULL));

	int number;
	for (int i=0; i<size_w; i++) {
		for (int j=0; j<size_h; j++) {
			number = rand()%elements;
			setCell(i,j,number);
			while (findMatch(i,j)) {
				number = rand()%elements;
				setCell(i,j,number);
			}
		}
	}
}

void Board::setCell(int x, int y, int value)
{
	m_logicBoard[x + (y*(m_iSize_w))] = value;
}

int Board::getCell(int x, int y)
{
	return m_logicBoard[x + (y*(m_iSize_w))];
}

std::vector<Vector2D> Board::returnAllMatches() {

	std::vector<Vector2D> matches;

	for (int i=0; i<m_iSize_w; i++) {
		for (int j=0; j<m_iSize_h; j++) {
			if (findMatch(i,j))
			{
				Vector2D match;
				match.setValue(i,j);
				matches.push_back(match);
			}
		}
	}
	return matches;
}

std::vector<Vector2D> Board::returnMatch(int startX, int startY) {
	
	std::vector<Vector2D> matches;
	
	Vector2D match;

	int value = getCell(startX,startY);
	int hmatches = 1;
	int vmatches = 1;

	//Looking to the left;
	if ((startX > 0) && (getCell(startX-1,startY) == value)) {
		hmatches++;
		match.setValue(startX-1,startY);
		matches.push_back(match);
		if ((startX > 1) && (getCell(startX-2,startY) == value)) {
			hmatches++;
			match.setValue(startX-2,startY);
			matches.push_back(match);
		}
	}
	//Looking to the right;
	if ((startX < (m_iSize_w-1)) && (getCell(startX+1,startY) == value)) {
		hmatches++;
		match.setValue(startX+1,startY);
		matches.push_back(match);
		if ((startX < (m_iSize_w-2)) && (getCell(startX+2,startY) == value)) {
			hmatches++;
			match.setValue(startX+2,startY);
			matches.push_back(match);
		} else if (hmatches==2) matches.pop_back();
	} else if (hmatches==2) matches.pop_back();

	//Looking to the top;
	if ((startY > 0) && (getCell(startX,startY-1) == value)) {
		vmatches++;
		match.setValue(startX,startY-1);
		matches.push_back(match);
		if ((startY > 1) && (getCell(startX,startY-2) == value)) {
			vmatches++;
			match.setValue(startX,startY-2);
			matches.push_back(match);
		}
	}
	//Looking to the bottom;
	if ((startY < (m_iSize_h-1)) && (getCell(startX,startY+1) == value)) {
		vmatches++;
		match.setValue(startX,startY+1);
		matches.push_back(match);
		if ((startY < (m_iSize_h-2)) && (getCell(startX,startY+2) == value)) {
			vmatches++;
			match.setValue(startX,startY+2);
			matches.push_back(match);
		} else if (vmatches==2) matches.pop_back();
	} else if (vmatches==2) matches.pop_back();

	if ((hmatches > 2) || (vmatches > 2))
	{
		match.setValue(startX,startY);
		matches.push_back(match);
	}
	
	return matches;
}

bool Board::findMatch(int startX, int startY) {

	int value = getCell(startX,startY);
	int hmatches = 1;
	int vmatches = 1;
	//Looking to the left;
	if ((startX > 0) && (getCell(startX-1,startY) == value)) {
		vmatches++;
		if ((startX > 1) && (getCell(startX-2,startY) == value)) {
			vmatches++;
		}
	}
	//Looking to the right;
	if ((startX < (m_iSize_w-1)) && (getCell(startX+1,startY) == value)) {
		vmatches++;
		if ((startX < (m_iSize_w-2)) && (getCell(startX+2,startY) == value)) {
			vmatches++;
		}
	}
	//Looking to the top;
	if ((startY > 0) && (getCell(startX,startY-1) == value)) {
		hmatches++;
		if ((startY > 1) && (getCell(startX,startY-2) == value)) {
			hmatches++;
		}
	}
	//Looking to the bottom;
	if ((startY < (m_iSize_h-1)) && (getCell(startX,startY+1) == value)) {
		hmatches++;
		if ((startY < (m_iSize_h-2)) && (getCell(startX,startY+2) == value)) {
			hmatches++;
		}
	}
	if ((hmatches > 2) || (vmatches > 2)) return true;
	return false;
}

void Board::removeCell(int x, int y)
{
	for (int i=y; i>0; i--)
	{
		m_logicBoard[x + (i*(m_iSize_w))] = m_logicBoard[x + ((i-1)*(m_iSize_w))];
	}

	m_logicBoard[x] = rand()%m_iElements;
}

bool Board::nextMove()
{
	Board* m_copyBoard = this;
	
	for (int i=0; i<m_iSize_w; i++) {
		for (int j=0; j<m_iSize_h; j++) {
			if (i>0)
			{
				int temp = m_copyBoard->getCell(i,j);
				m_copyBoard->setCell(i,j,m_copyBoard->getCell(i-1,j));
				m_copyBoard->setCell(i-1,j,temp);
				if (m_copyBoard->findMatch(i,j))
				{ 
					return true;
				}
			}
		}
	}
	return false;
}
	