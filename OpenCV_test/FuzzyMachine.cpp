#include "pch.h"
#include "FuzzyMachine.h"
#include <iostream>


FuzzyMachine::FuzzyMachine(double pStart, double pEnd, double sStart, double sEnd)
{
	this->pStart = pStart;
	this->pEnd = pEnd;
	this->sStart = sStart;
	this->sEnd = sEnd;
}


FuzzyMachine::~FuzzyMachine()
{
}

double FuzzyMachine::FuzzyFunction(double start, double end, double step, double value)
{
	double result = 0;
	double halfStep = step / 2;
	if (value < start + halfStep) {
		result = (1 / step)*((value - start) + halfStep);
	}
	else if (start >= 0 && value < start + step + halfStep)
	{
		return 1;
	}
	else {
		result = 1 - ((1 / step)*((value - end) + halfStep));
	}
	if (result < 0) {
		return 0;
	}
	return result;
	return 0.0f;
}

double FuzzyLeft(double start, double step, double value) {
	double result = 0;
	double halfStep = step / 2;
	if (value < start - halfStep) {
		return 1;
	}
	result = 1 - ((1 / step)*((value - start) + halfStep));
	if (result < 0){
		result = 0;
	}
	return result;
}

double FuzzyRight(double end, double step, double value) {
	double result = 0;
	double halfStep = step / 2;
	if (value > end + halfStep) {
		return 1;
	}
	result = (1 / step)*((value - end) + halfStep);
	if (result < 0) {
		result = 0;
	}
	return result;

}

void FuzzyMachine::CalculateSegregationClass(double sizeValue, double proportionValue)
{
	double sStep = (sEnd - sStart) / 4;
	double S1 = FuzzyLeft(sStart, sStep, sizeValue);
	double S2 = FuzzyFunction(0.002, 0.004, sStep, sizeValue);
	double S3 = FuzzyFunction(0.004, 0.006, sStep, sizeValue);
	double S4 = FuzzyRight(sEnd, sStep, sizeValue);
	double pStep = (pEnd - pStart) / 4;
	double P1 = FuzzyLeft(pStart, pStep, proportionValue);
	double P2 = FuzzyFunction(0.2, 0.25, pStep, proportionValue);
	double P3 = FuzzyFunction(0.25, 0.3, pStep, proportionValue);
	double P4 = FuzzyRight(pEnd, pStep, proportionValue);

	std::cout << "Segregation Class: \n";

	if (P1 > 0) {
		if (S1 > 0) {
			std::cout << "1: " << P1 * S1 << "\n";
		}
		if (S2 > 0) {
			std::cout << "1 (1,5): " << P1 * S2 << "\n";
		}
		if (S3 > 0) {
			std::cout << "1 (1,5): " << P1 * S3 << "\n";
		}
		if (S4 > 0) {
			std::cout << "1 (1,5): " << P1 * S4 << "\n";
		}
	}
	if (P2 > 0) {
		if (S1 > 0) {
			std::cout << "1: " << P2 * S1 << "\n";
		}
		if (S2 > 0) {
			std::cout << "2 (1,5): " << P2 * S2 << "\n";
		}
		if (S3 > 0) {
			std::cout << "2 (1,5): " << P2 * S3 << "\n";
		}
		if (S4 > 0) {
			std::cout << "2 (1,5): " << P2 * S4 << "\n";
		}
	}
	if (P3 > 0) {
		if (S1 > 0) {
			std::cout << "1 (1,5): " << P3 * S1 << "\n";
		}
		if (S2 > 0) {
			std::cout << "1 (1,5): " << P3 * S2 << "\n";
		}
		if (S3 > 0) {
			std::cout << "1 (1,5): " << P3 * S3 << "\n";
		}
		if (S4 > 0) {
			std::cout << "1/2 (1,5): " << P3 * S4 << "\n";
		}
	}
	if (P4 > 0) {
		if (S1 > 0) {
			std::cout << "2: " << P4 * S1 << "\n";
		}
		if (S2 > 0) {
			std::cout << "3: " << P4 * S2 << "\n";
		}
		if (S3 > 0) {
			std::cout << "3: " << P4 * S3 << "\n";
		}
		if (S4 > 0) {
			std::cout << "3: " << P4 * S4 << "\n";
		}
	}
	
	int tmp;

}
