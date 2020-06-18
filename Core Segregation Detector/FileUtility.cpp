#include "FileUtility.h"



FileUtility::FileUtility()
{
}

void FileUtility::WriteResultToFile(double size, double intensity, List<double>^ segregation)
{
	std::ofstream myfile;
	myfile.open("example.csv", std::ios::app);
	myfile << size << ';' << intensity << ';' << segregation[0] << ';' << segregation[1] << ';' << segregation[2] << ';' << segregation[3] << ';' << std::endl;
	myfile.close();

}
