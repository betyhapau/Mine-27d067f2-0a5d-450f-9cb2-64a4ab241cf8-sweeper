#include "UIManager.h"
#include "Grid.h"
#include "SDL.h"
#include <iostream>

#define windowWidth 700
#define windowHeight 700

#define fps 16 // 1000 / 60

using namespace std;


UIManager::UIManager()
{
	this->window = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);
}

UIManager::~UIManager()
{
}

void UIManager::Setup()
{
	this->createWindow();
	this->setWindowScreen();
}

void UIManager::GenerateGrid(Grid grid)
{
}

void UIManager::Update()
{
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
	this->window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);

	if (this->window == NULL)
	{
		cout << "init error: " << SDL_GetError();
	}
}

void UIManager::setWindowScreen()
{
	this->screen = SDL_GetWindowSurface(this->window);

	// Change things at the rendering level
	Uint32 backgroundColor = SDL_MapRGB(this->screen->format, 18, 52, 86);
	SDL_FillRect(this->screen, NULL, backgroundColor);
	SDL_UpdateWindowSurface(this->window);
}
