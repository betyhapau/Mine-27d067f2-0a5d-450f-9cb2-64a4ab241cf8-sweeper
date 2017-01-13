#include "UIManager.h"
#include "GameManager.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include <string>

#define buttonEscapeValue 9

#define verticalEmptySpace 50
#define cellSizeUI 34
#define buttonWidthUI 102

#define fps 16 // 1000 / 60

using namespace std;

UIManager::UIManager(GameManager* gameManager)
{
	this->windowWidth = 0;
	this->windowHeight = 0;
	this->rows = 0;
	this->columns = 0;
	this->flags = 0;
	this->window = NULL;
	this->screen = NULL;
	this->gameMng = gameManager;

	SDL_Init(SDL_INIT_EVERYTHING);
}

UIManager::~UIManager()
{
}

void UIManager::Setup(int numberOfRows, int numberOfColumns, int flags)
{
	this->rows = numberOfRows;
	this->columns = numberOfColumns;
	this->flags = flags;
	this->windowHeight = (cellSizeUI * 2 + verticalEmptySpace + this->rows * cellSizeUI);
	this->windowWidth = this->columns * cellSizeUI;

	this->createWindow();
	this->setWindowScreen();

	this->GenerateWindowContent();
}

void UIManager::GenerateWindowContent()
{
	this->createUIButtons();
	this->createUIFlagIndicator();
	this->createUIGrid();

	SDL_UpdateWindowSurface(this->window);
}

void UIManager::Update()
{
	// Listen to events
	Uint32 start_tick = NULL;
	SDL_Event event;
	bool running = true;

	while (running)
	{
		start_tick = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;

				SDL_Quit();
				break;
			}
			else if(event.type == SDL_MOUSEBUTTONUP)
			{
				if (!this->gameMng->HasGameEnded) 
				{
					this->handleClick(event.button);
				}
			}
		}

		limitFramerate(start_tick);
	}
}

void UIManager::ShowEmpty(int i, int j)
{
	this->uiGridCells[i][j]->ChangeImage("ArtRes/EmptyCell.bmp");

	SDL_UpdateWindowSurface(this->window);
}

void UIManager::ShowNumber(int i, int j, int number)
{
	this->uiGridCells[i][j]->ChangeImage(this->getCellImagePath(number));

	SDL_UpdateWindowSurface(this->window);
}

void UIManager::ShowBomb()
{
	this->uiGridCells[this->CurrentClickedCellRow][this->CurrentClickedCellColumn]->ChangeImage("ArtRes/ClickedBombCell.bmp");

	SDL_UpdateWindowSurface(this->window);
}

void UIManager::limitFramerate(Uint32 start_tick)
{
	Uint32 tickDifference = SDL_GetTicks() - start_tick;
	if (fps > tickDifference) {
		SDL_Delay(fps - tickDifference);
	}
}

void UIManager::createWindow()
{
	if (this->window == NULL) 
	{
		this->window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, SDL_WINDOW_SHOWN);
	}
	else
	{
		SDL_SetWindowSize(this->window, this->windowWidth, this->windowHeight);
	}
}

void UIManager::setWindowScreen()
{
	this->screen = SDL_GetWindowSurface(this->window);

	// Change things at the rendering level
	Uint32 backgroundColor = SDL_MapRGB(this->screen->format, 0, 0, 0);
	SDL_FillRect(this->screen, NULL, backgroundColor);
	SDL_UpdateWindowSurface(this->window);
}

void UIManager::createUIButtons()
{
	// Create easy mode button
	UICoordinates* easyModeButtonCoord = new UICoordinates(0, buttonWidthUI, 0, cellSizeUI);
	UIElement* easyModeButton = new UIElement(easyModeButtonCoord, "ArtRes/EasyButton.bmp", this->screen);

	// Create medium mode button
	UICoordinates* mediumModeButtonCoord = new UICoordinates(buttonWidthUI, buttonWidthUI * 2, 0, cellSizeUI);
	UIElement* mediumModeButton = new UIElement(mediumModeButtonCoord, "ArtRes/MediumButton.bmp", this->screen);
	
	// Create hard mode button
	UICoordinates* hardModeButtonCoord = new UICoordinates(buttonWidthUI * 2, buttonWidthUI * 3, 0, cellSizeUI);
	UIElement* hardModeButton = new UIElement(hardModeButtonCoord, "ArtRes/HardButton.bmp", this->screen);

	this->uiButtons.push_back(easyModeButton);
	this->uiButtons.push_back(mediumModeButton);
	this->uiButtons.push_back(hardModeButton);
}

void UIManager::createUIFlagIndicator()
{
	// Create first digit
	UICoordinates* firstDigitCoord = new UICoordinates(0, cellSizeUI, cellSizeUI, cellSizeUI*2);
	UIElement* firstDigit = new UIElement(firstDigitCoord, "ArtRes/Cell0.bmp", this->screen);

	// Create second digit
	UICoordinates* secondDigitCoord = new UICoordinates(cellSizeUI, cellSizeUI * 2, cellSizeUI, cellSizeUI * 2);
	UIElement* secondDigit = new UIElement(secondDigitCoord, "ArtRes/Cell0.bmp", this->screen);

	this->uiFlagNumber.push_back(firstDigit);
	this->uiFlagNumber.push_back(secondDigit);

	this->setFlagNumber();
}

void UIManager::createUIGrid()
{
	int gridStartPositionY = cellSizeUI * 2 + verticalEmptySpace;
	std::vector<UIElement*> cells(this->columns);
	for (int i = 0; i < this->rows; i++)
	{
		cells.clear();
		for (int j = 0; j < this->columns; j++)
		{
			UICoordinates* cellCoord = new UICoordinates(cellSizeUI * j, cellSizeUI * (j + 1), gridStartPositionY + cellSizeUI *i, gridStartPositionY + cellSizeUI * (i + 1));
			UIElement* currentCell = new UIElement(cellCoord, "ArtRes/UnclickedCell.bmp", this->screen);
			cells.push_back(currentCell);
		}

		this->uiGridCells.push_back(cells);
	}
}

void UIManager::handleClick(SDL_MouseButtonEvent event)
{
	int buttonClicked = this->checkIfButtonClicked(event.x, event.y);
	if (buttonClicked != buttonEscapeValue)
	{
		this->gameMng->ChangeGameDifficulty(buttonClicked);
		return;
	}

	if (this->checkIfGridClicked(event.x, event.y)) 
	{
		if (event.button == SDL_BUTTON_LEFT)
		{
			this->onLeftClick();
		}
		else if (event.button == SDL_BUTTON_RIGHT)
		{
			if (this->gameMng->ToggleFlag())
			{
				if (this->flags != 0) 
				{
					this->flags--;
					this->uiGridCells[this->CurrentClickedCellRow][this->CurrentClickedCellColumn]->ChangeImage("ArtRes/FlagCell.bmp");
				}
			}
			else
			{
				this->flags++;
				this->uiGridCells[this->CurrentClickedCellRow][this->CurrentClickedCellColumn]->ChangeImage("ArtRes/UnclickedCell.bmp");
			}

			this->setFlagNumber();
		}

		SDL_UpdateWindowSurface(this->window);
	}
}

int UIManager::checkIfButtonClicked(int x, int y)
{
	int resultButtonNumber = buttonEscapeValue;

	if (y <= cellSizeUI) 
	{
		if (x <= buttonWidthUI) 
		{
			return 0;
		}
		else if(x <= buttonWidthUI * 2)
		{
			return 1;
		}
		else if (x <= buttonWidthUI * 3) 
		{
			return 2;
		}
	}

	return resultButtonNumber;
}

bool UIManager::checkIfGridClicked(int x, int y)
{
	int gridStartPositionY = cellSizeUI * 2 + verticalEmptySpace;

	if (y > gridStartPositionY) 
	{
		this->CurrentClickedCellRow = (y - gridStartPositionY) / cellSizeUI;
		this->CurrentClickedCellColumn = x / cellSizeUI;

		return true;
	}

	return false;
}

void UIManager::setFlagNumber()
{
	this->uiFlagNumber[0]->ChangeImage(this->getCellImagePath(this->flags / 10));
	this->uiFlagNumber[1]->ChangeImage(this->getCellImagePath(this->flags % 10));
}

void UIManager::onLeftClick()
{
	this->gameMng->OnLeftClick();
}

char* UIManager::getCellImagePath(int number)
{
	char integer_string[32];
	sprintf_s(integer_string, "%d", number);

	char* str = new char[16];
	strcpy(str, "ArtRes/Cell");
	strcat(str, integer_string);
	strcat(str, ".bmp");

	return str;
}
