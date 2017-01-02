#pragma once
#include "GridCell.h"
#include <vector>

class Grid
{
private:
	int columns;
	int rows;
	int numberOfBombs;
	GridCell gridWithCells[100][100];

	void CreateGrid();
	std::vector<unsigned int> GetRandomBombPositions();
	void GetElements(int index, int j, std::vector<GridCell> &neighbours);


public:
	Grid(int rowNr, int columnNr, int bombNr);
	~Grid();

	void GenerateGrid();
	void Reset();
};

