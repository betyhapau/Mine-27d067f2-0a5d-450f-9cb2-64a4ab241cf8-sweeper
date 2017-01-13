#include "UICoordinates.h"
#include "SDL.h"
#pragma once

class UIElement
{
private:
	UICoordinates* elementCoordinates;
	SDL_Surface* image;
	SDL_Surface* screen;
	SDL_Rect elementRect;

	void drawImage();

public:
	UIElement(UICoordinates* elementCoordinates, char imagePathWithName[], SDL_Surface* screen);
	~UIElement();

	void ChangeImage(char imagePathWithName[]);
};

