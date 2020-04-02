#pragma once
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>

//using namespace cv;

ref class CircleDetector
{
public:
	CircleDetector(cv::Mat&, cv::Mat&);
	//~CircleDetector();
	cv::Vec3f DetectCircle();

private:
	cv::Mat* src;
	cv::Mat* hist;
	int tresholdColor;

	float LineLenght(cv::Point, cv::Point);
	cv::Point GetEdgePoint(cv::Point, cv::Vec2f);
};