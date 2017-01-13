#include "Grid.h"
#pragma once

class GameManager
{
private:
	Grid* grid;
public:
	unsigned int GameMode;

	GameManager();
	~GameManager();

	void StartGame();
	void ChangeGameDifficulty(unsigned int gameMode);
};

