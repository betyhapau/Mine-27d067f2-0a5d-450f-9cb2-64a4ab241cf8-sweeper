#pragma once

class Grid;
class UIManager;

class GameManager
{
private:
	Grid* grid;
	UIManager* uiManager;

public:
	bool HasGameEnded;
	int GameMode;

	GameManager();
	~GameManager();

	void StartGame();
	void ChangeGameDifficulty(int gameMode);
	bool ToggleFlag();
	void OnLeftClick();
};

