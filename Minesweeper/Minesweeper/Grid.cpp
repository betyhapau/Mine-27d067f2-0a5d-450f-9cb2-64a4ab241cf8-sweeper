#include "Grid.h"
#include "GridCell.h"
#include "GameManager.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

Grid::Grid(int rowNr, int columnNr, int bombNr, GameManager* gameManager)
{
	this->rows = rowNr;
	this->columns = columnNr;
	this->numberOfBombs = bombNr;
	this->gameMng = gameManager;

	this->CreateGrid();
}

Grid::~Grid()
{
}

// Generates the grid
void Grid::GenerateGrid() 
{
	std::vector<int> randomPositions = GetRandomBombPositions();
	
	int rowOrColumn = rows < columns ? columns : rows;

	for (unsigned i = 0; i < randomPositions.size(); i++)
	{
		this->gridWithCells[randomPositions[i] / rowOrColumn][randomPositions[i] % rowOrColumn]->SetBomb();
	}
}

void Grid::ShowGrid() 
{
	for (int i = 0; i < rows; i++)
	{
		std::cout << "[ ";

		for (int j = 0; j < columns; j++)
		{
			if (this->gridWithCells[i][j]->HasBomb == true)
			{
				std::cout << "b ";
				continue;
			}

			std::cout << this->gridWithCells[i][j]->BombNeighboursNumber;
			std::cout << " ";
			
		}
		std::cout << "]\n";
	}
}

bool Grid::ToggleFlag(int i, int j)
{
	if (this->gridWithCells[i][j]->HasFlag) {
		this->gridWithCells[i][j]->HasFlag = false;
	}
	else
	{
		this->gridWithCells[i][j]->HasFlag = true;
	}

	return this->gridWithCells[i][j]->HasFlag;
}

bool Grid::HasBomb(int i, int j)
{
	return this->gridWithCells[i][j]->HasBomb;
}

int Grid::HasNumber(int i, int j)
{
	return this->gridWithCells[i][j]->BombNeighboursNumber;
}

// Resets the GridCells
void Grid::Reset() 
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			this->gridWithCells[i][j]->Reset();
		}
	}

	this->GenerateGrid();
}

// Creates the Grid according to rows and columns
void Grid::CreateGrid() 
{
	std::vector<GridCell*> cells (this->columns);
	for (int i = 0; i < this->rows; i++)
	{
		cells.clear();
		for (int j = 0; j < this->columns; j++)
		{
			GridCell* currentCell = new GridCell(i, j);
			cells.push_back(currentCell);
		}

		this->gridWithCells.push_back(cells);
	}

	std::vector<GridCell*> neighbours;

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			this->GetElements(i, j, neighbours);
			neighbours.pop_back();

			if (i - 1 >= 0)
			{
				this->GetElements(i - 1, j, neighbours);
			}

			if (i + 1 < rows)
			{
				this->GetElements(i + 1, j, neighbours);
			}
			
			this->gridWithCells[i][j]->SetNeighbours(neighbours);

			neighbours.clear();
		}
	}

	this->GenerateGrid();
}

void Grid::GetElements(int index, int j, std::vector<GridCell*> &neighbours)
{
	if (j - 1 >= 0) 
	{
		neighbours.push_back(this->gridWithCells[index][j - 1]);
	}

	if (j + 1 < this->columns)
	{
		neighbours.push_back(this->gridWithCells[index][j + 1]);
	}

	neighbours.push_back(this->gridWithCells[index][j]);
}

// Generates the random positions for the bombs in the current grid
std::vector<int> Grid::GetRandomBombPositions()
{
	std::vector<int> v, result (this->numberOfBombs);

	for (int i = 0; i< this->rows * this->columns; i++) {
		v.push_back(i);
	}
	
	// shuffle the initial vector and get the first numberOfBombs elements
	std::random_shuffle(v.begin(), v.end());
	std::copy(v.begin(), v.begin() + this->numberOfBombs, result.begin());

	return result;
}