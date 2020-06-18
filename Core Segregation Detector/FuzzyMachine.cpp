//#include "pch.h"
#include "FuzzyMachine.h"
#include <iostream>
#include <fl/Headers.h>

using namespace fl;


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

List<double>^ FuzzyMachine::RunCalculation(double size, double intensity)
{
	Engine* engine = new Engine;
	engine->setName("Segregator");
	engine->setDescription("");

	InputVariable* Size = new InputVariable;
	Size->setName("Size");
	Size->setDescription("size of area highlighted as a segregation in percentage of entire examinated area");
	Size->setEnabled(true);
	Size->setRange(0.000, 0.400);
	Size->setLockValueInRange(false);
	Size->addTerm(Discrete::create("very_small", 6, 0.000, 1.000, 0.015, 1.000, 0.100, 0.000));
	Size->addTerm(Discrete::create("small", 8, 0.000, 0.000, 0.025, 1.000, 0.035, 1.000, 0.100, 0.000));
	Size->addTerm(Discrete::create("medium", 8, 0.000, 0.000, 0.045, 1.000, 0.055, 1.000, 0.100, 0.000));
	Size->addTerm(Discrete::create("large", 6, 0.000, 0.000, 0.065, 1.000, 0.100, 1.000));
	engine->addInputVariable(Size);

	InputVariable* Intensity = new InputVariable;
	Intensity->setName("Intensity");
	Intensity->setDescription("mean intensity of highlithed area when compared with image color parameters");
	Intensity->setEnabled(true);
	Intensity->setRange(0.000, 0.400);
	Intensity->setLockValueInRange(false);
	Intensity->addTerm(Discrete::create("very_small", 6, 0.000, 1.000, 0.175, 1.000, 0.400, 0.000));
	Intensity->addTerm(Discrete::create("small", 8, 0.000, 0.000, 0.215, 1.000, 0.235, 1.000, 0.400, 0.000));
	Intensity->addTerm(Discrete::create("medium", 8, 0.000, 0.000, 0.275, 1.000, 0.285, 1.000, 0.400, 0.000));
	Intensity->addTerm(Discrete::create("large", 6, 0.000, 0.000, 0.315, 1.000, 0.400, 1.000));

	
	engine->addInputVariable(Intensity);


	OutputVariable* Segregation = new OutputVariable;
	Segregation->setName("Segregation");
	Segregation->setDescription("");
	Segregation->setEnabled(true);
	Segregation->setRange(1.000, 4.000);
	Segregation->setLockValueInRange(false);
	Segregation->setAggregation(new Maximum);
	Segregation->setDefuzzifier(new Centroid());
	Segregation->setDefaultValue(fl::nan);
	Segregation->setLockPreviousValue(false);
	Segregation->addTerm(Discrete::create("1", 6, 1.000, 1.000, 2.250, 0.000, 4.000, 0.000));
	Segregation->addTerm(Discrete::create("1_5", 6, 1.000, 0.000, 1.435, 1.000, 1.850, 0.000));
	Segregation->addTerm(Discrete::create("2", 6, 1.000, 0.000, 1.800, 1.000, 2.775, 0.000));
	Segregation->addTerm(Discrete::create("3", 6, 1.935, 0.000, 2.915, 1.000, 4.000, 0.000));
	Segregation->addTerm(Discrete::create("4", 4, 2.750, 0.000, 4.000, 1.000));
	engine->addOutputVariable(Segregation);

	RuleBlock* ruleBlock = new RuleBlock;
	ruleBlock->setName("");
	ruleBlock->setDescription("");
	ruleBlock->setEnabled(true);
	ruleBlock->setConjunction(new Minimum);
	ruleBlock->setDisjunction(new Maximum);
	ruleBlock->setImplication(new Minimum);
	ruleBlock->setActivation(new General);
	ruleBlock->addRule(Rule::parse("if Size is very_small and Intensity is very_small then Segregation is 1", engine));
	ruleBlock->addRule(Rule::parse("if Size is small and Intensity is very_small then Segregation is 1_5", engine));
	ruleBlock->addRule(Rule::parse("if Size is medium and Intensity is very_small then Segregation is 1_5", engine));
	ruleBlock->addRule(Rule::parse("if Size is large and Intensity is very_small then Segregation is 1_5", engine));

	ruleBlock->addRule(Rule::parse("if Size is very_small and Intensity is small then Segregation is 1", engine));
	ruleBlock->addRule(Rule::parse("if Size is small and Intensity is small then Segregation is 1_5", engine));
	ruleBlock->addRule(Rule::parse("if Size is medium and Intensity is small then Segregation is 2", engine));
	ruleBlock->addRule(Rule::parse("if Size is large and Intensity is small then Segregation is 2", engine));

	ruleBlock->addRule(Rule::parse("if Size is very_small and Intensity is medium then Segregation is 1_5", engine));
	ruleBlock->addRule(Rule::parse("if Size is small and Intensity is medium then Segregation is 1_5", engine));
	ruleBlock->addRule(Rule::parse("if Size is medium and Intensity is medium then Segregation is 2", engine));
	ruleBlock->addRule(Rule::parse("if Size is large and Intensity is medium then Segregation is 2", engine));

	ruleBlock->addRule(Rule::parse("if Size is very_small and Intensity is large then Segregation is 2", engine));
	ruleBlock->addRule(Rule::parse("if Size is small and Intensity is large then Segregation is 3", engine));
	ruleBlock->addRule(Rule::parse("if Size is medium and Intensity is large then Segregation is 3", engine));
	ruleBlock->addRule(Rule::parse("if Size is large and Intensity is large then Segregation is 3", engine));

	engine->addRuleBlock(ruleBlock);

	Size->setValue(size);
	Intensity->setValue(intensity);
	engine->process();

	/*double s1 = Segregation1->getValue();
	double s2 = Segregation2->getValue();
	double s3 = Segregation3->getValue();
	double s4 = Segregation4->getValue();*/

	double s1 = engine->getOutputVariable(0)->fuzzyOutput()->getTerm(0).getDegree();
	double s2 = engine->getOutputVariable(0)->fuzzyOutput()->getTerm(1).getDegree();
	double s3 = engine->getOutputVariable(0)->fuzzyOutput()->getTerm(2).getDegree();
	double s4 = engine->getOutputVariable(0)->fuzzyOutput()->getTerm(3).getDegree();


	FisExporter* exporter = new FisExporter();
	exporter->toFile("testFile_2.fis", engine);

	List<double>^ engineOutput = gcnew List<double>();
	engineOutput->Add(s1);
	engineOutput->Add(s2);
	engineOutput->Add(s3);
	engineOutput->Add(s4);

	return engineOutput;
}

List<double>^ FuzzyMachine::CalculateSegregation(double size, double intensity)
{
	//Engine* engine = FisImporter().fromFile("FuzzyLogicDefinition.fis");
	Engine* engine = FisImporter().fromFile("testFile_2.fis");
	engine->setInputValue("Size", size);
	engine->setInputValue("Intensity", intensity);
	engine->process();

	List<double>^ engineOutput = gcnew List<double>();
	engineOutput->Add(engine->getOutputVariable(0)->fuzzyOutput()->getTerm(0).getDegree());
	engineOutput->Add(engine->getOutputVariable(0)->fuzzyOutput()->getTerm(1).getDegree());
	engineOutput->Add(engine->getOutputVariable(0)->fuzzyOutput()->getTerm(2).getDegree());
	engineOutput->Add(engine->getOutputVariable(0)->fuzzyOutput()->getTerm(3).getDegree());

	return engineOutput;
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
	if (result < 0) {
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
