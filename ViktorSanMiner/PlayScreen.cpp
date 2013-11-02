#include "PlayScreen.h"
#include "Game.h"
#include "TextureManager.h"
#include "MouseManager.h"
#include "SoundManager.h"
#include "TextManager.h"

const std::string PlayScreen::s_playID = "PLAY";

void PlayScreen::update()
{
	m_pCells->update();

	if (m_pCells->isMoving()) return;

	matchesManager();		//this is to check if new matches emerge from the new board configuration after a match3.

	if(MyMouseManager::Instance()->getMouseButtonState(LEFT))
	{
		if(!inClick)
		{
			Vector2D* screenSelected = MyMouseManager::Instance()->getMousePosition();
			Vector2D* cellSelected1 = convertScreenCoordToBoardCoords(screenSelected);

			if ((firstCellSelected->getX()==999) &&						//select the first jewel
				(cellSelected1->getX() > -1) &&
				(cellSelected1->getY() > -1) &&
				(cellSelected1->getX() < NUMBER_OF_TILES_W) &&
				(cellSelected1->getY() < NUMBER_OF_TILES_H))
			{
				firstCellSelected=cellSelected1;
				screenSelectedFirstCell.setValue(screenSelected->getX(),screenSelected->getY());
			}
			else if (firstCellSelected->distance(cellSelected1))	//second click, select the second jewel and try to switch
			{
				secondCellSelected=cellSelected1;
				intercambia(firstCellSelected->getX(),firstCellSelected->getY(),secondCellSelected->getX(),secondCellSelected->getY());
			}
			else													//second jewel not in range, frees the first jewel
			{
				firstCellSelected->setValue(999,999);
			}
			inClick=true;	//filtering the button down state
		}
		else if (firstCellSelected->getX()!=999)					//I'm still onClick so I'm selecting second jewel by drag
		{
			Vector2D* screenSelected = MyMouseManager::Instance()->getMousePosition();
			int deltaX = screenSelected->getX() - screenSelectedFirstCell.getX();
			int deltaY = screenSelected->getY() - screenSelectedFirstCell.getY();
			if ((deltaX > (CELL_SIZE_W/2)) && (firstCellSelected->getX() < (NUMBER_OF_TILES_W-1) ))	//mouse moving to the right
			{
				Vector2D* cellSelected2 = new Vector2D;
				cellSelected2->setValue(firstCellSelected->getX()+1,firstCellSelected->getY());
				secondCellSelected=cellSelected2;
				intercambia(firstCellSelected->getX(),firstCellSelected->getY(),secondCellSelected->getX(),secondCellSelected->getY());
				screenSelectedFirstCell.setValue(screenSelected->getX(),screenSelected->getY());
				cellSelected2 = NULL;
				delete cellSelected2;
			}
			else if ((deltaX < (CELL_SIZE_W/-2)) && (firstCellSelected->getX() > 0 ))	//mouse moving to the left
			{
				Vector2D* cellSelected2 = new Vector2D;
				cellSelected2->setValue(firstCellSelected->getX()-1,firstCellSelected->getY());
				secondCellSelected=cellSelected2;
				intercambia(firstCellSelected->getX(),firstCellSelected->getY(),secondCellSelected->getX(),secondCellSelected->getY());
				screenSelectedFirstCell.setValue(screenSelected->getX(),screenSelected->getY());
				cellSelected2 = NULL;
				delete cellSelected2;
			}
			else if ((deltaY > (CELL_SIZE_H/2)) && (firstCellSelected->getY() < (NUMBER_OF_TILES_H-1) ))	//mouse moving to the bottom
			{
				Vector2D* cellSelected2 = new Vector2D;
				cellSelected2->setValue(firstCellSelected->getX(),firstCellSelected->getY()+1);
				secondCellSelected=cellSelected2;
				intercambia(firstCellSelected->getX(),firstCellSelected->getY(),secondCellSelected->getX(),secondCellSelected->getY());
				screenSelectedFirstCell.setValue(screenSelected->getX(),screenSelected->getY());
				cellSelected2 = NULL;
				delete cellSelected2;
			}
			else if ((deltaY < (CELL_SIZE_H/-2)) && (firstCellSelected->getY() > 0 ))	//mouse moving to the top
			{
				Vector2D* cellSelected2 = new Vector2D;
				cellSelected2->setValue(firstCellSelected->getX(),firstCellSelected->getY()-1);
				secondCellSelected=cellSelected2;
				intercambia(firstCellSelected->getX(),firstCellSelected->getY(),secondCellSelected->getX(),secondCellSelected->getY());
				screenSelectedFirstCell.setValue(screenSelected->getX(),screenSelected->getY());
				cellSelected2 = NULL;
				delete cellSelected2;
			}
		}
	} 
	else		//button released, ready to second click or start over
	{
		inClick=false;
	}

	m_pFuse->update(SDL_GetTicks() - m_iTimeInit);
	if ((SDL_GetTicks()-m_iTimeInit) > GAME_TIME)
	{
		MyGame::Instance()->setScore(m_iScore);
		MyGame::Instance()->endPlay();
	}
}

void PlayScreen::render()
{
	m_pBackground->drawAtPos(0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);

	m_pCells->draw();
	m_pFuse->draw();

	if (firstCellSelected->getX()!=999)
	{
		m_pSelected->drawAtPos(BOARD_X + (firstCellSelected->getX()*CELL_SIZE_W),BOARD_Y +(firstCellSelected->getY()*CELL_SIZE_H),CELL_SIZE_W,CELL_SIZE_H);
	}

	SDL_Color texto = {0, 0, 0};

	std::string score = std::to_string(m_iScore);

	MyTextManager::Instance()->drawText(("score: " + score),"resources/fonts/animeace_i.ttf",20,300,55,texto);

}

bool PlayScreen::onEnter()
{
	if(!MyTextureManager::Instance()->load("resources/BackGround.jpg","background",MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/selected.png", "selected", MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/Blue.png", "jewel1", MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/Green.png", "jewel2", MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/Purple.png", "jewel3", MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/Red.png",	"jewel4", MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/Yellow.png", "jewel5", MyGame::Instance()->getRenderer())) return false;
	if(!MyTextureManager::Instance()->load("resources/bonus.png", "bonus", MyGame::Instance()->getRenderer())) return false;

	if(!MySoundManager::Instance()->load("resources/audio/bgMusic.wav","bgMusic",SOUND_MUSIC)) return false;
	if(!MySoundManager::Instance()->load("resources/audio/match0.wav","break1",SOUND_SFX)) return false;
	if(!MySoundManager::Instance()->load("resources/audio/match1.wav","break2",SOUND_SFX)) return false;
	if(!MySoundManager::Instance()->load("resources/audio/match2.wav","break3",SOUND_SFX)) return false;
	if(!MySoundManager::Instance()->load("resources/audio/match3.wav","break4",SOUND_SFX)) return false;
	if(!MySoundManager::Instance()->load("resources/audio/badswap.wav","badswap",SOUND_SFX)) return false;
	
	MySoundManager::Instance()->playMusic("bgMusic",-1);

	m_pBackground = new GameObject();
	m_pBackground->init(0,0,"background");

	m_pSelected = new GameObject;
	m_pSelected->init(0,0,"selected");

	std::vector<Vector2D> fusePath;

	Vector2D fuseNode;
	fuseNode.setValue(262,553);fusePath.push_back(fuseNode);
	fuseNode.setValue(251,543);fusePath.push_back(fuseNode);
	fuseNode.setValue(252,515);fusePath.push_back(fuseNode);
	fuseNode.setValue(213,506);fusePath.push_back(fuseNode);
	fuseNode.setValue(209,448);fusePath.push_back(fuseNode);
	fuseNode.setValue(207,372);fusePath.push_back(fuseNode);
	fuseNode.setValue(178,372);fusePath.push_back(fuseNode);

	m_pFuse = new Fuse(60000,6,fusePath);

	firstCellSelected = new Vector2D;
	firstCellSelected->setValue(999,999);

	secondCellSelected = new Vector2D;
	secondCellSelected->setValue(999,999);

	m_pBoard = new Board(NUMBER_OF_TILES_W,NUMBER_OF_TILES_H,ELEMENTS);

	m_pCells = new Cells(NUMBER_OF_TILES_W,NUMBER_OF_TILES_H,CELL_SIZE_W,CELL_SIZE_H);

	for (int i=0; i<NUMBER_OF_TILES_W; i++) {
		for (int j=0; j<NUMBER_OF_TILES_H; j++) {
			m_pCells->setCell(i,j,createCell(i,j,m_pBoard->getCell(i,j)));
		}
	}

	changedBoard = false;
	inClick = false;

	m_iScore = 0;

	m_iTimeInit = SDL_GetTicks();

	return true;
}

bool PlayScreen::onExit()
{
	m_pBackground->clean();
	m_pSelected->clean();
	m_pCells->clean();

	delete firstCellSelected;
	delete secondCellSelected;

	MyTextureManager::Instance()->clearFromTextureMap("background");
	MyTextureManager::Instance()->clearFromTextureMap("selected");
	MyTextureManager::Instance()->clearFromTextureMap("jewel1");
	MyTextureManager::Instance()->clearFromTextureMap("jewel2");
	MyTextureManager::Instance()->clearFromTextureMap("jewel3");
	MyTextureManager::Instance()->clearFromTextureMap("jewel4");
	MyTextureManager::Instance()->clearFromTextureMap("jewel5");

	MySoundManager::Instance()->stopMusic();

	return true;
}

Vector2D* PlayScreen::convertScreenCoordToBoardCoords(Vector2D* screenCoords)
{
	Vector2D* boardCoords = new Vector2D;

	boardCoords->setValue((screenCoords->getX() - BOARD_X)/(CELL_SIZE_W),(screenCoords->getY() - BOARD_Y)/(CELL_SIZE_H));

	return boardCoords;
}

void PlayScreen::intercambia(int x1, int y1, int x2, int y2)
{
	if ((x1 > NUMBER_OF_TILES_W-1) || (x1 < 0) ||
		(x2 > NUMBER_OF_TILES_W-1) || (x2 < 0) ||
		(y1 > NUMBER_OF_TILES_H-1) || (y1 < 0) ||
		(y2 > NUMBER_OF_TILES_H-1) || (y2 < 0)) return;

	int temp = m_pBoard->getCell(x1,y1);
	m_pBoard->setCell(x1,y1,m_pBoard->getCell(x2,y2));
	m_pBoard->setCell(x2,y2,temp);

	GameObject* tempCell = m_pCells->getCell(x1,y1);
	m_pCells->getCell(x1,y1)->moveTo(m_pCells->getCell(x2,y2)->getActualX(),m_pCells->getCell(x2,y2)->getActualY());
	m_pCells->getCell(x2,y2)->moveTo(tempCell->getActualX(),tempCell->getActualY());

	m_pCells->setCell(x1,y1,m_pCells->getCell(x2,y2));
	m_pCells->setCell(x2,y2,tempCell);
}

void PlayScreen::removeCell(int x, int y)
{
	if ((m_pCells->getCell(x,y)->isBonus()) && ((SDL_GetTicks()-m_iTimeInit) > BONUS_TIME)) 
	{
		m_iTimeInit += BONUS_TIME;
	}

	m_iScore +=CELL_SCORE;
	m_pBoard->removeCell(x,y);
	m_pCells->removeCell(x,y);
	m_pCells->setCell(x,0,createCell(x,0,m_pBoard->getCell(x,0)));
}

GameObject* PlayScreen::createCell(int x, int y, int value)
{
	GameObject* newObject = new GameObject();
	
	switch (value) {
	case 0:		newObject->init(x*CELL_SIZE_W,(y)*CELL_SIZE_H,"jewel1");break;
	case 1:		newObject->init(x*CELL_SIZE_W,(y)*CELL_SIZE_H,"jewel2");break;
	case 2:		newObject->init(x*CELL_SIZE_W,(y)*CELL_SIZE_H,"jewel3");break;
	case 3:		newObject->init(x*CELL_SIZE_W,(y)*CELL_SIZE_H,"jewel4");break;
	case 4:		newObject->init(x*CELL_SIZE_W,(y)*CELL_SIZE_H,"jewel5");break;
	}

	if ((rand()%CHANCE_OF_BONUS) == 1)
		newObject->setBonus(true);

	return newObject;
}

void PlayScreen::matchesManager()
{
	if (secondCellSelected->getX()!=999)		//we will only check after a sucessful move, don't want to do all the frames
	{
		std::vector<Vector2D> matches1 = m_pBoard->returnMatch(firstCellSelected->getX(),firstCellSelected->getY());
		std::vector<Vector2D> matches2 = m_pBoard->returnMatch(secondCellSelected->getX(),secondCellSelected->getY());

		if (matches1.size() > 2)															//if there is match3
		{
			for (std::vector<Vector2D>::size_type i=0; i!=matches1.size(); i++)
			{
				if (matches1[i].getY() < firstCellSelected->getY())							//if is above the reference cell, we remove the reference cell
					matches1[i].setValue(matches1[i].getX(), firstCellSelected->getY());
				else if (matches1[i].getY() > firstCellSelected->getY())					//if is below the reference cell, we move down the reference cell
					firstCellSelected->setValue(firstCellSelected->getX(), firstCellSelected->getY()+1);

				removeCell(matches1[i].getX(),matches1[i].getY());
			}
			changedBoard = true;
		}

		if (matches2.size() > 2)
		{
			for (std::vector<Vector2D>::size_type i=0; i!=matches2.size(); i++)
			{
				if (matches2[i].getY() < secondCellSelected->getY())
					matches2[i].setValue(matches2[i].getX(), secondCellSelected->getY());
				else if (matches2[i].getY() > secondCellSelected->getY())
					secondCellSelected->setValue(secondCellSelected->getX(), secondCellSelected->getY()+1);

				removeCell(matches2[i].getX(),matches2[i].getY());
			}
			changedBoard = true;
		}
		if ((matches1.size() < 3) && (matches2.size() < 3))
		{
			intercambia(firstCellSelected->getX(),firstCellSelected->getY(),secondCellSelected->getX(),secondCellSelected->getY());
			MySoundManager::Instance()->playSound("badswap",0);
		} else
		{
			soundEffect();
		}

		firstCellSelected->setValue(999,999);
		secondCellSelected->setValue(999,999);
	} else if (changedBoard) {
		std::vector<Vector2D> matchesBoard = m_pBoard->returnAllMatches();
		if (matchesBoard.size() > 1)
		{
			SDL_Delay(250); 
			soundEffect();
		}
		else changedBoard = false;
		for (std::vector<Vector2D>::size_type i=0; i!=matchesBoard.size(); i++)
		{
			removeCell(matchesBoard[i].getX(),matchesBoard[i].getY());
		}
	}
}

void PlayScreen::soundEffect()
{
	switch(rand()%4)
	{
	case 0:
		MySoundManager::Instance()->playSound("break1",0);break;
	case 1:
		MySoundManager::Instance()->playSound("break2",0);break;
	case 2:
		MySoundManager::Instance()->playSound("break3",0);break;
	case 3:
		MySoundManager::Instance()->playSound("break4",0);break;
	}
}