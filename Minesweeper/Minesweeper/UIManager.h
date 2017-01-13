#include "SDL.h"
#include "UIElement.h"
#include <vector>
#pragma once

class GameManager;

class UIManager
{

private:
	int windowWidth;
	int windowHeight;
	int rows;
	int columns;
	int flags;
	SDL_Window *window; 
	SDL_Surface *screen;
	std::vector<UIElement*> uiButtons;
	std::vector<UIElement*> uiFlagNumber;
	std::vector< std::vector<UIElement*> > uiGridCells;
	GameManager* gameMng;

	void limitFramerate(Uint32 start_tick);
	void createWindow();
	void setWindowScreen();
	void createUIButtons();
	void createUIFlagIndicator();
	void createUIGrid();
	void handleClick(SDL_MouseButtonEvent event);
	int checkIfButtonClicked(int x, int y);
	bool checkIfGridClicked(int x, int y);
	void setFlagNumber();
	void onLeftClick();
	char* getCellImagePath(int number);

public:
	int CurrentClickedCellColumn;
	int CurrentClickedCellRow;

	UIManager(GameManager* gameManager);
	~UIManager();

	void Setup(int numberOfRows, int numberOfColumns, int flags);
	void GenerateWindowContent();
	void Update();
	void ShowEmpty(int i, int j);
	void ShowNumber(int i, int j, int number);
	void ShowBomb();
};

