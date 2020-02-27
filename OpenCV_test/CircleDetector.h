#pragma once
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>

using namespace cv;

class CircleDetector
{
public:
	CircleDetector(Mat, Mat);
	~CircleDetector();
	Vec3f DetectCircle();

private:
	Mat src;
	Mat hist;
	int tresholdColor;

	float LineLenght(Point, Point);
	Point GetEdgePoint(Point, Vec2f);
};
