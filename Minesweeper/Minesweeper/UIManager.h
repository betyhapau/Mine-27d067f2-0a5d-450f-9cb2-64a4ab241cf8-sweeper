#include "SDL.h"
#include "Grid.h"
#pragma once

class UIManager
{

private:
	SDL_Window *window; 
	SDL_Surface *screen;
	void limitFramerate(Uint32 start_tick);
	void createWindow();
	void setWindowScreen();

public:
	UIManager();
	~UIManager();

	void Setup();
	void GenerateGrid(Grid* grid);
	void Update();
};

