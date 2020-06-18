#include "Automata.h"


Automata::Automata(List<List<Cell^>^>^ dataGrid, float meanRange)
{
	this->dataGrid = dataGrid;
	newDataGrid = dataGrid;
	outerRingActiveCellsNumber = -1;
	this->meanRange = meanRange;
	innerActiveSegmentNumber = 0;
	innerActiveValueSum = 0;
}

Automata::~Automata()
{
}

List<List<Cell^>^>^ Automata::runNaiveEvolution(int tresholdValue, int neighboursNumber)
{
	List<Cell^>^ tmpNeighbours;
	int tmpCount = 0;
	outerRingActiveCellsNumber = 0;
	for (int i = 0; i < dataGrid->Count; i++) {
		List<Cell^>^ datagridRow = dataGrid[i];
		List<Cell^>^ newdatagridRow = newDataGrid[i];
		for (int j = 0; j < dataGrid[i]->Count; j++) {

			if (!datagridRow[j]->active || datagridRow[j]->value >= tresholdValue || !datagridRow[j]->automatonActive) {
				datagridRow[j]->automatonActive = false;
				continue;
			}
			tmpNeighbours = getVonNeumannNeighbours(i, j);
			for (int iterator = 0; iterator < tmpNeighbours->Count; iterator++)
			{
				if (tmpNeighbours[iterator]->value < tresholdValue && tmpNeighbours[iterator]->active && tmpNeighbours[iterator]->automatonActive) {
					tmpCount++;
				}
			}
			if (tmpCount >= neighboursNumber) {
				newdatagridRow[j]->automatonActive = true;
				if (datagridRow[j]->distanceToCenter > meanRange) {
					outerRingActiveCellsNumber++;
				}
				else {
					innerActiveSegmentNumber++;
					innerActiveValueSum += datagridRow[j]->value;
				}
			}
			else {
				newdatagridRow[j]->automatonActive = false;
			}
			tmpCount = 0;
		}
		newDataGrid[i] = newdatagridRow;
	}
	dataGrid = newDataGrid;
	return dataGrid;
}

List<Cell^>^ Automata::getVonNeumannNeighbours(int x, int y)
{
	List<Cell^>^ result = gcnew List<Cell^>;
	if (x > 0 && y < dataGrid[x - 1]->Count) {
		List<Cell^>^ tmpDataGrid = dataGrid[x - 1];
		result->Add(tmpDataGrid[y]);
	}
	if (y > 0) {
		List<Cell^>^ tmpDataGrid = dataGrid[x];
		result->Add(tmpDataGrid[y - 1]);
	}

	if (x < dataGrid->Count - 2 && y < dataGrid[x + 1]->Count) {
		List<Cell^>^ tmpDataGrid = dataGrid[x + 1];
		result->Add(tmpDataGrid[y]);
	}
	if (y < dataGrid[x]->Count - 2) {
		List<Cell^>^ tmpDataGrid = dataGrid[x];
		result->Add(tmpDataGrid[y + 1]);
	}
	return result;

}
