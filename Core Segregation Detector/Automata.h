#pragma once

#include "Cell.h"
//#include <vector>
//#include "stdafx.h"
using namespace System;
using namespace System::Collections::Generic;
//using namespace std;

ref class Automata
{
public:
	Automata(List<List<Cell^>^>^ dataGrid, float);
	~Automata();
	List<List<Cell^>^>^ runNaiveEvolution(int tresholdValue, int neighboursNumber);
	int outerRingActiveCellsNumber;
	int innerActiveSegmentNumber;
	double innerActiveValueSum;

private:
	float meanRange;
	List<List<Cell^>^>^ dataGrid;
	List<List<Cell^>^>^ newDataGrid;
	List<Cell^>^ getVonNeumannNeighbours(int x, int y);
};