#pragma once

//#include "pch.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <msclr\marshal_cppstd.h>
#include <cmath>
#include "Cell.h"
#include "Automata.h"
#include "FuzzyMachine.h"
#include "CircleDetector.h"
#include<fstream>
#include "ImageUtility.h"



ref class MainEngine
{
public:
	MainEngine();
	MainEngine(System::String^);
	void RunCalculation();
	//void RunCalculation(std::string);
	System::String^ filePath;
	System::Drawing::Bitmap^ originalImage;
	System::Drawing::Bitmap^ editedImage;
	void SetPath(System::String^);
	Boolean originalImageReady;
	Boolean editedImageReady;
	Boolean calculationsReady;
private:
	cv::Mat DrawHistogram(cv::Mat);
	void DrawCircle(cv::Mat, cv::Vec3f);
	float CalcDistance(float, float, float, float);
	float CalcAvgColor(cv::Mat, float, float, float, float);
	void DrawGrid(cv::Mat, List<List<Cell^>^>^, float);
	void DrawGrid(cv::Mat, List<List<Cell^>^>^);
};

