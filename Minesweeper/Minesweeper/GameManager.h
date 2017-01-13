#pragma once

class Grid;
class UIManager;

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
	void SetFlag();
};

