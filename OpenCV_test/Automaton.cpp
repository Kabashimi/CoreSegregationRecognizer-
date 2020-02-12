#include "pch.h"
#include "Automaton.h"


Automaton::Automaton(vector<vector<Cell>> dataGrid)
{
	this->dataGrid = dataGrid;
	newDataGrid = dataGrid;
}

Automaton::~Automaton()
{
}

vector<vector<Cell>> Automaton::runNaiveEvolution(int tresholdValue, int neighboursNumber)
{
	vector<Cell> tmpNeighbours;
	int tmpCount = 0;
	for (int i = 0; i < dataGrid.size(); i++) {
		for (int j = 0; j < dataGrid[i].size(); j++) {
			if (!dataGrid[i][j].active || dataGrid[i][j].value >= tresholdValue || !dataGrid[i][j].automatonActive) {
				newDataGrid[i][j].automatonActive = false;
				continue;
			}
			/*if (dataGrid[i][j].value < tresholdValue) {
				dataGrid[i][j].automatonActive = true;
			}*/
			tmpNeighbours = getVonNeumannNeighbours(i, j);
			for (int iterator = 0; iterator < tmpNeighbours.size(); iterator++)
			{
				if (tmpNeighbours[iterator].value < tresholdValue && tmpNeighbours[iterator].active && tmpNeighbours[iterator].automatonActive) {
					tmpCount++;
				}
			}
			if (tmpCount >= neighboursNumber) {
				newDataGrid[i][j].automatonActive = true;
			}
			else {
				newDataGrid[i][j].automatonActive = false;
			}
			tmpCount = 0;
		}
	}
	dataGrid = newDataGrid;
	return dataGrid;
}

vector<Cell> Automaton::getVonNeumannNeighbours(int x, int y)
{
	vector<Cell> result;
	if (x > 0 && y < dataGrid[x - 1].size()) {
		result.push_back(dataGrid[x - 1][y]);
	}
	if (y > 0) {
		result.push_back(dataGrid[x][y - 1]);
	}

	if (x < dataGrid.size() - 2 && y < dataGrid[x + 1].size()) {
		result.push_back(dataGrid[x + 1][y]);
	}
	if (y < dataGrid[x].size() - 2) {
		result.push_back(dataGrid[x][y + 1]);
	}
	return result;

}
