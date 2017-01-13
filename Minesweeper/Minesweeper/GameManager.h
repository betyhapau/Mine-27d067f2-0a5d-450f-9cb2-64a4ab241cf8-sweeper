#include "Grid.h"
#include "UIManager.h"
#pragma once

class GameManager
{
private:
	Grid* grid;
	UIManager* uiManager;

public:
	int GameMode;

	GameManager();
	~GameManager();

	void StartGame();
	void ChangeGameDifficulty(int gameMode);
};

