#include "UIElement.h"
#include "UICoordinates.h"
#include "SDL.h"

void UIElement::drawImage()
{
	SDL_BlitSurface(this->image, NULL, this->screen, &elementRect);
}

UIElement::UIElement(UICoordinates* elementCoordinates, char imagePathWithName[], SDL_Surface* screen)
{
	this->elementCoordinates = elementCoordinates;
	this->screen = screen;

	this->ChangeImage(imagePathWithName);
}

UIElement::~UIElement()
{
}

void UIElement::ChangeImage(char imagePathWithName[])
{
	this->image = SDL_LoadBMP(imagePathWithName);

	this->elementRect = this->image->clip_rect;

	this->elementRect.x = elementCoordinates->x1;
	this->elementRect.y = elementCoordinates->y1;

	this->drawImage();
}
