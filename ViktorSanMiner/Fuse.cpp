#include "Fuse.h"
#include "Game.h"


Fuse::Fuse(Uint32 totalTime, Uint32 sections, std::vector<Vector2D> positions)
{
	m_iTotalTime = totalTime;
	m_iSections = sections;
	m_fusePath = positions;

	MyTextureManager::Instance()->load("resources/spark1.png","spark1",MyGame::Instance()->getRenderer());
	MyTextureManager::Instance()->load("resources/spark2.png","spark2",MyGame::Instance()->getRenderer());
	MyTextureManager::Instance()->load("resources/spark3.png","spark3",MyGame::Instance()->getRenderer());
}

void Fuse::update(Uint32 tiempo)
{
	Uint32 sectionLength = m_iTotalTime/m_iSections;
	int actualSection = tiempo/sectionLength;
	int inSectionPosition = tiempo%sectionLength;

	int posX = m_fusePath[actualSection+1].getX() - m_fusePath[actualSection].getX();
	int posY = m_fusePath[actualSection+1].getY() - m_fusePath[actualSection].getY();

	float perCent = (float)inSectionPosition/(float)sectionLength;

	m_iPosX = m_fusePath[actualSection].getX() + ((float)posX * perCent);
	m_iPosY = m_fusePath[actualSection].getY() + ((float)posY * perCent);
}

void Fuse::draw()
{
	switch (rand()%3)
	{
	case 0:	MyTextureManager::Instance()->draw("spark1",m_iPosX-25,m_iPosY-25,50,50,MyGame::Instance()->getRenderer());break;
	case 1:	MyTextureManager::Instance()->draw("spark2",m_iPosX-25,m_iPosY-25,50,50,MyGame::Instance()->getRenderer());break;
	case 2:	MyTextureManager::Instance()->draw("spark3",m_iPosX-25,m_iPosY-25,50,50,MyGame::Instance()->getRenderer());break;
	}
}

Fuse::~Fuse(void)
{
}
