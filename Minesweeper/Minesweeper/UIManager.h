#include "SDL.h"
#include "UIElement.h"
#include <vector>
#pragma once

class UIManager
{

private:
	int windowWidth;
	int windowHeight;
	int rows;
	int columns;
	SDL_Window *window; 
	SDL_Surface *screen;
	std::vector<UIElement*> uiButtons;
	std::vector<UIElement*> uiFlagNumber;
	std::vector< std::vector<UIElement*> > uiGridCells;

	void limitFramerate(Uint32 start_tick);
	void createWindow();
	void setWindowScreen();
	void createUIButtons();
	void createUIFlagIndicator();
	void createUIGrid();

public:
	UIManager();
	~UIManager();

	void Setup(int numberOfRows, int numberOfColumns);
	void GenerateWindowContent();
	void Update();
};

