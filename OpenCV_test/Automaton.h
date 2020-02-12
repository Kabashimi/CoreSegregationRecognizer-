#pragma once
#include "Cell.h"
#include <vector>
using namespace std;

class Automaton
{
public:
	Automaton(vector<vector<Cell>> dataGrid);
	~Automaton();
	vector<vector<Cell>> runNaiveEvolution(int tresholdValue, int neighboursNumber);

private:
	vector<vector<Cell>> dataGrid;
	vector<vector<Cell>> newDataGrid;
	vector<Cell> getVonNeumannNeighbours(int x, int y);
};

