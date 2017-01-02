#pragma once
#include "GridCell.h"
#include <vector>

class Grid
{
private:
	int columns;
	int rows;
	int numberOfBombs;
	std::vector< std::vector<GridCell> > gridWithCells;

	void CreateGrid();
	std::vector<int> GetRandomBombPositions();
	void GetElements(int index, int j, std::vector<GridCell*> &neighbours);


public:
	Grid(int rowNr, int columnNr, int bombNr);
	~Grid();

	void GenerateGrid();
	void Reset();
	void ShowGrid();
};

