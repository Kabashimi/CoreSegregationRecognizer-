#include "FileUtility.h"



FileUtility::FileUtility()
{
}

void FileUtility::WriteResultToFile(double size, double intensity, double segregation)
{
	std::ofstream myfile;
	myfile.open("example.csv");
	myfile << size << ';' << intensity << ';' << segregation << std::endl;
	myfile.close();

}
