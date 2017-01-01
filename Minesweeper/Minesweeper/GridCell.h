#pragma once
#include <vector>

class GridCell
{
private:
	std::vector<GridCell> neighbours;
	void InformNeighboursBombWasAdded();
public:
	bool HasFlag;
	bool HasBomb;
	bool IsVisible;
	int BombNeighboursNumber;

	GridCell();
	~GridCell();

	void SetNeighbours(std::vector<GridCell> neighbourCells);
	void SetBomb();
	void Reset();
};

