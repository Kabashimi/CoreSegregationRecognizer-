#include "pch.h"
#include "CircleDetector.h"


CircleDetector::CircleDetector(Mat src, Mat hist)
{
	float prevValue = 0;
	float value;
	bool passedMaximum = false;
	int minimum;

	for (int i = 0; i < 256; i++) {
		value = hist.at<float>(i);
		//std::cout << "v:" << value << endl;
		if (prevValue > value) {
			passedMaximum = true;
		}
		if (passedMaximum) {
			if (prevValue < value) {
				minimum = i;
				break;
			}
		}
		prevValue = value;
	}

	tresholdColor = minimum;
}


CircleDetector::~CircleDetector()
{
}

Vec3f CircleDetector::DetectCircle()
{
	   	
}
