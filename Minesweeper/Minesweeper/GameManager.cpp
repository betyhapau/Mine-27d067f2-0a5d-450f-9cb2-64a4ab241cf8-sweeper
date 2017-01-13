#include "GameManager.h"
#include "Grid.h"
#include "UIManager.h"

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
	this->grid = NULL;
	this->uiManager = NULL;
}

GameManager::~GameManager()
{
}

void GameManager::StartGame()
{
	this->uiManager = new UIManager(this);
	this->ChangeGameDifficulty(1);
}

void GameManager::ChangeGameDifficulty(int gameMode)
{
	this->HasGameEnded = false;
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

	this->grid = new Grid(rows, columns, bombs, this);
	this->uiManager->Setup(rows, columns, bombs);
	this->uiManager->Update();
}

bool GameManager::ToggleFlag()
{
	return this->grid->ToggleFlag(this->uiManager->CurrentClickedCellRow, this->uiManager->CurrentClickedCellColumn);
}

void GameManager::OnLeftClick()
{
	int row = this->uiManager->CurrentClickedCellRow;
	int column = this->uiManager->CurrentClickedCellColumn;

	if (this->grid->HasBomb(row, column))
	{
		this->HasGameEnded = true;
		this->uiManager->ShowBomb();
		return;
	}

	int nrOfNeighbourBombs = this->grid->HasNumber(row, column);

	if (nrOfNeighbourBombs != 0)
	{
		this->uiManager->ShowNumber(row, column, nrOfNeighbourBombs);
	}
}

void GameManager::ShowEmpty()
{
	int number;
	for (int i = 0; i < this->grid->RowsList.size(); i++)
	{
		number = this->grid->NumberList[i];
		if (number == 0)
		{
			this->uiManager->ShowEmpty(this->grid->RowsList[i], this->grid->ColumnsList[i]);
		}
		else
		{
			this->uiManager->ShowNumber(this->grid->RowsList[i], this->grid->ColumnsList[i], number);
		}
	}
}


