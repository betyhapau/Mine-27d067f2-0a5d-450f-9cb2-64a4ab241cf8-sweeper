#pragma once
#include <vector>

class GridCell
{
private:
	void InformNeighboursBombWasAdded();


public:
	std::vector<GridCell*> neighbours;
	bool HasFlag;
	bool HasBomb;
	bool IsVisible;
	int x;
	int y;
	int BombNeighboursNumber;

	GridCell(int xIndex, int yIndex);
	GridCell();
	~GridCell();

	void SetNeighbours(std::vector<GridCell*> neighbourCells);
	void SetBomb();
	void Reset();
};

