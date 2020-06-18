#pragma once
#include <iostream>
#include <fstream>
using namespace System::Collections::Generic;

ref class FileUtility
{
public:
	FileUtility();
	static void WriteResultToFile(double, double, List<double>^);
};

