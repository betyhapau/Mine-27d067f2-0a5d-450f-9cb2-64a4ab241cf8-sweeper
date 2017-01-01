#include "GridCell.h"
#include <vector>

using namespace std;

GridCell::GridCell()
{
	Reset();
}


GridCell::~GridCell()
{
}

// Sets the neighbours of the current grid cell
void GridCell::SetNeighbours(vector<GridCell> neighbourCells) {
	neighbours = neighbourCells;
}

// Sets the bomb on current grid cell
void GridCell::SetBomb() {
	HasFlag = true;

	InformNeighboursBombWasAdded();
}

// Resets the current grid cell
void GridCell::Reset() {
	HasFlag = false;
	HasBomb = false;
	IsVisible = false;
	BombNeighboursNumber = 0;

	neighbours.clear();
}

void GridCell::InformNeighboursBombWasAdded() {
	for (unsigned i = 0; i < neighbours.size(); i++) {
		neighbours[i].BombNeighboursNumber++;
	}
}