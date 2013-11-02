#include "Cells.h"


Cells::Cells(int w, int h, int cellW, int cellH)
{
	m_iWidth = w;
	m_iHeight = h;
	m_iCellSizeW = cellW;
	m_iCellSizeH = cellH;
	m_cells = new GameObject*[m_iWidth*m_iHeight];
	for (int i=0; i<m_iWidth*m_iHeight; i++)
	{
		m_cells[i] = NULL;
	}
}

void Cells::initCell(int x, int y, std::string textureID)
{
	m_cells[x + (y*m_iWidth)]->init(x,y,textureID);
}

void Cells::update()
{
	m_bMoving = false;
	for (int i=0; i<m_iWidth; i++) {
		for (int j=0; j<m_iHeight; j++) {
			m_cells[i+ (j*m_iWidth)]->update();
			m_bMoving = m_bMoving || getCell(i,j)->isMoving();
		}
	}
}

void Cells::draw()
{
	for (int i=0; i<m_iWidth; i++) {
		for (int j=0; j<m_iHeight; j++) {
			m_cells[i+ (j*m_iWidth)]->draw();
		}
	}
}


GameObject* Cells::getCell(int x, int y)
{
	return m_cells[x + (y*m_iWidth)];
}

void Cells::setCell(int x, int y, GameObject* cell)
{
	if (m_cells[x + (y*m_iWidth)]!=NULL)
	{
		m_cells[x + (y*m_iWidth)] = NULL;
		delete m_cells[x + (y*m_iWidth)];
	}
	m_cells[x + (y*m_iWidth)] = cell;
}

void Cells::removeCell(int x, int y)
{
	for (int i = y; i > 0; i--)
	{
		this->getCell(x,i-1)->moveTo(x*m_iCellSizeW,i*m_iCellSizeH);
		this->setCell(x,i,this->getCell(x,i-1));
	}
}

Cells::~Cells(void)
{
	
}

void Cells::clean()
{
	for (int i=0; i<m_iWidth*m_iHeight; i++)
	{
		if (m_cells[i]!=NULL)
		{
			m_cells[i] = NULL;
			delete m_cells[i];
		}
	}
	m_cells = NULL;
	delete[] m_cells;
}
