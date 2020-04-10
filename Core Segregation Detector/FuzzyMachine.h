#pragma once
//#include <fl/Headers.h>

//using namespace fl;

ref class FuzzyMachine
{
public:
	FuzzyMachine(double, double, double, double);
	~FuzzyMachine();

	double FuzzyFunction(double start, double end, double step, double value);
	void CalculateSegregationClass(double, double);

	double pStart, pEnd, sStart, sEnd;
};

