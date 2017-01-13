#include "GameManager.h"
#include<iostream>
#include<string>

using namespace std;

int main(int argc, char **argv) 
{
	/*int rows, columns, bombs;

	cout << "Rows:";
	cin >> rows;

	cout << "Columns:";
	cin >> columns;

	cout << "Bombs:";
	cin >> bombs;

	Grid* grid = new Grid(rows, columns, bombs);

	grid->GenerateGrid();
	grid->ShowGrid();

	cin >> rows;*/

	GameManager* gameManager = new GameManager();

	gameManager->StartGame();

	return 0;
}