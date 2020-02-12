#pragma once
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class CircleDetector
{
public:
	CircleDetector(Mat, Mat);
	~CircleDetector();

private:
	Mat src;
	Mat hist;
	int tresholdColor;

	Vec3f DetectCircle();
};

