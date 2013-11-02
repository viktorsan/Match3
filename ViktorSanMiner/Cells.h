#pragma once
#include "GameObject.h"

class Cells
{
public:
	Cells(int w, int h, int cellW, int cellH);
	~Cells(void);

	void initCell(int i, int j, std::string textureID);
	void update();
	void draw();

	void clean();

	GameObject* getCell(int i, int j);				//returns the cell in position i,j
	void setCell(int i, int j, GameObject* cell);	//set the position i,j with cell, deletes the former cell
	void removeCell(int i, int j);					//deletes a cell and make the column fall
	bool isMoving() {return m_bMoving;}				//true is there is at least one cell moving

private:

	int m_iWidth, m_iHeight;
	int m_iCellSizeW, m_iCellSizeH;

	GameObject** m_cells;
	bool m_bMoving;
};

