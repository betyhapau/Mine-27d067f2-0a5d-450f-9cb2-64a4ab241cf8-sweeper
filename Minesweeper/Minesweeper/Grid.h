#include "GridCell.h"
#include <vector>
#pragma once

class GameManager;

class Grid
{
private:
	int columns;
	int rows;
	int numberOfBombs;
	std::vector< std::vector<GridCell*> > gridWithCells;
	GameManager* gameMng;

	void CreateGrid();
	std::vector<int> GetRandomBombPositions();
	void GetElements(int index, int j, std::vector<GridCell*> &neighbours);


public:
	Grid(int rowNr, int columnNr, int bombNr, GameManager* gameManager);
	~Grid();

	void GenerateGrid();
	void Reset();
	void ShowGrid();
	bool ToggleFlag(int i, int j);
	bool HasBomb(int i, int j);
	int HasNumber(int i, int j);
};

