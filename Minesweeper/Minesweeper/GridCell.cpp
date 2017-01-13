#include "GridCell.h"
#include <vector>

using namespace std;

GridCell::GridCell(int xIndex, int yIndex)
{
	this->x = yIndex;
	this->y = xIndex;
	this->Reset();
}

GridCell::GridCell()
{
}

GridCell::~GridCell()
{
}

// Sets the neighbours of the current grid cell
void GridCell::SetNeighbours(vector<GridCell*> neighbourCells) 
{
	this->neighbours = neighbourCells;
}

// Sets the bomb on current grid cell
void GridCell::SetBomb() 
{
	this->HasBomb = true;

	this->InformNeighboursBombWasAdded();
}

// Resets the current grid cell
void GridCell::Reset() 
{
	this->HasFlag = false;
	this->HasBomb = false;
	this->IsVisible = false;
	this->BombNeighboursNumber = 0;
	
	this->neighbours.clear();
}

void GridCell::InformNeighboursBombWasAdded() 
{
	for (unsigned i = 0; i < this->neighbours.size(); i++)
	{
		(this->neighbours[i])->BombNeighboursNumber++;
	}
}