#include "SDL.h"
#include "Grid.h"
#include<iostream>
#include<string>

#define windowWidth 700
#define windowHeight 700

#define fps 16 // 1000 / 60


using namespace std;

void limitFramerate(Uint32 start_tick) 
{
	Uint32 tickDifference = SDL_GetTicks() - start_tick;
	if (fps > tickDifference) {
		SDL_Delay(fps - tickDifference);
	}
}

int main(int argc, char **argv) 
{
	/*int rows, columns, bombs;

	cout << "Rows:";
	cin >> rows;

	cout << "Columns:";
	cin >> columns;

	cout << "Bombs:";
	cin >> bombs;

	Grid* grid = new Grid(rows, columns, bombs);

	grid->GenerateGrid();
	grid->ShowGrid();

	cin >> rows;*/

	/*
		Currently following tutorials at: https://www.youtube.com/watch?v=iggmjJ_C_C4&list=PL1H1sBF1VAKXMz8kETLHRo1LwnvB08Q2J
	*/

	SDL_Init(SDL_INIT_EVERYTHING);

	// Creating the window
	SDL_Window *window = NULL;
	window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);

	if (window == NULL) 
	{
		cout << "init error: " << SDL_GetError();
	}


	// Change things at the rendering level
	SDL_Surface *screen = SDL_GetWindowSurface(window);
	Uint32 backgroundColor = SDL_MapRGB(screen->format, 18, 52, 86);
	SDL_FillRect(screen, NULL, backgroundColor);
	SDL_UpdateWindowSurface(window);

	// Listen to events
	Uint32 start_tick = NULL;
	SDL_Event ev;
	bool running = true;

	while (running)
	{
		start_tick = SDL_GetTicks();

		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT) 
			{
				running = false;
				break;
			}
		}

		limitFramerate(start_tick);
	}

	SDL_Quit();

	return 0;
}