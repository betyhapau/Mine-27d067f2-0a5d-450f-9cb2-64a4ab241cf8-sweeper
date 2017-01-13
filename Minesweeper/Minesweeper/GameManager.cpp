#include "GameManager.h"
#include "Grid.h"

#define verticalEmptySpace 
#define cellSizeUI 34
#define buttonWidthUI 102

#define easyRowNumber 9
#define easyColumnNumber 9
#define easyBombNumber 10

#define mediumRowNumber 16
#define mediumColumnNumber 16
#define mediumBombNumber 40

#define hardRowNumber 16
#define hardColumnNumber 30
#define hardBombNumber 99


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::StartGame()
{
	this->ChangeGameDifficulty(0);


}

void GameManager::ChangeGameDifficulty(unsigned int gameMode)
{
	if (this->GameMode == gameMode)
	{
		if (this->grid != NULL)
		{
			this->grid->Reset();
		}

		return;
	}

	this->GameMode = gameMode;
	int rows, columns, bombs;

	if (gameMode == 0)
	{
		rows = easyRowNumber;
		columns = easyColumnNumber;
		bombs = easyBombNumber;
	}
	else if (gameMode == 1)
	{
		rows = mediumRowNumber;
		columns = mediumColumnNumber;
		bombs = mediumBombNumber;
	}
	else
	{
		rows = hardRowNumber;
		columns = hardColumnNumber;
		bombs = hardBombNumber;
	}

	this->grid = new Grid(rows, columns, bombs);
}


