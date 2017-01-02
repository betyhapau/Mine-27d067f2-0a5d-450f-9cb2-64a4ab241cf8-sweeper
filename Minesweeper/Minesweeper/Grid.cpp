#include "Grid.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

Grid::Grid(int rowNr, int columnNr, int bombNr) 
{
	rows = rowNr;
	columns = columnNr;
	numberOfBombs = bombNr;

	CreateGrid();
}


Grid::~Grid()
{
}

// Generates the grid
void Grid::GenerateGrid() 
{
	std::vector<unsigned int> randomPositions = GetRandomBombPositions();
	
	for (unsigned i = 0; i < randomPositions.size(); i++)
	{
		gridWithCells[randomPositions[i] % rows][randomPositions[i] % columns].SetBomb();
	}
}

// Resets the GridCells
void Grid::Reset() 
{
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
		{
			gridWithCells[i][j].Reset();
		}
	}
}

// Creates the Grid according to rows and columns
void Grid::CreateGrid() 
{
	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < columns; j++)
		{
			GridCell* currentCell = new GridCell();
			gridWithCells[i][j] = *currentCell;
		}
	}

	std::vector<GridCell> neighbours;

	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
		{
			GetElements(i, j, neighbours);
			neighbours.pop_back();

			if (i - 1 >= 0)
			{
				GetElements(i - 1, j, neighbours);
			}

			if (i + 1 < rows)
			{
				GetElements(i + 1, j, neighbours);
			}
			
			gridWithCells[i][j].SetNeighbours(neighbours);

			neighbours.clear();
		}
	}

}

void Grid::GetElements(int index, int j, std::vector<GridCell> &neighbours)
{
	if (j - 1 >= 0) 
	{
		neighbours.push_back(gridWithCells[index][j - 1]);
	}

	if (j + 1 < columns)
	{
		neighbours.push_back(gridWithCells[index][j + 1]);
	}

	neighbours.push_back(gridWithCells[index][j]);
}

// Generates the random positions for the bombs in the current grid
std::vector<unsigned int> Grid::GetRandomBombPositions()
{
	std::vector<unsigned int> v, result;

	for (unsigned i = 0; i< rows * columns; i++) {
		v.push_back(i);
	}
	
	// shuffle the initial vector and get the first numberOfBombs elements
	std::random_shuffle(v.begin(), v.end());
	std::copy(v.begin(), v.begin() + numberOfBombs, result.begin());

	return result;
}