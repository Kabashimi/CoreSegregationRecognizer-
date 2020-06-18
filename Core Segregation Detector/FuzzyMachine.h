#pragma once
#include <vector>
using namespace System::Collections::Generic;
//#include <fl/Headers.h>

//using namespace fl;

ref class FuzzyMachine
{
public:
	FuzzyMachine(double, double, double, double);
	~FuzzyMachine();

	static List<double>^ RunCalculation(double, double);
	double FuzzyFunction(double start, double end, double step, double value);
	void CalculateSegregationClass(double, double);
	static List<double>^ CalculateSegregation(double, double);

	double pStart, pEnd, sStart, sEnd;
};

