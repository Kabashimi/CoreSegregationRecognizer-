//#include "pch.h"
#include "CircleDetector.h"


CircleDetector::CircleDetector(cv::Mat& src, cv::Mat& hist)
{
	float prevValue = 0;
	float value;
	bool passedMaximum = false;
	int minimum;
	std::vector<float> meanHist;

	for (int i = 0; i < 250; i += 5) {
		float meanHistSum = hist.at<float>(i);
		meanHistSum += hist.at<float>(i + 1);
		meanHistSum += hist.at<float>(i + 2);
		meanHistSum += hist.at<float>(i + 3);
		meanHistSum += hist.at<float>(i + 4);
		meanHist.push_back(meanHistSum / 5);
	}

	//find edge color value - between circle and outer space
	//for (int i = 0; i < 256; i++) {
	//	value = hist.at<float>(i);
	//	//std::cout << "v:" << value << std::endl;
	//	if (prevValue > value) {
	//		passedMaximum = true;
	//	}
	//	if (passedMaximum) {
	//		if (prevValue < value) {
	//			minimum = i;
	//			break;
	//		}
	//	}
	//	prevValue = value;
	//}

	for (int i = 0; i < 50; i++) {
		//value = hist.at<float>(i);
		value = meanHist[i];
		//std::cout << "v:" << value << std::endl;
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

	this->src = &src;
	this->hist = &hist;
	tresholdColor = minimum * 5;
}


//CircleDetector::~CircleDetector()
//{
//}

cv::Vec3f CircleDetector::DetectCircle()
{
	cv::Vec3f mainCircle;
	cv::Point center;

	//Get center point
	center.x = src->cols / 2;
	center.y = src->rows / 2;
	if (src->at<uchar>(center) < tresholdColor) {
		std::cout << "ERROR: Center point is ot inside circle\n";
	}

	//Get 4 point on circle edge
	cv::Point A = GetEdgePoint(center, cv::Vec2f(1.0, 0.0));
	cv::Point B = GetEdgePoint(center, cv::Vec2f(-1.0, 0.0));
	cv::Point C = GetEdgePoint(center, cv::Vec2f(0.0, 1.0));
	cv::Point D = GetEdgePoint(center, cv::Vec2f(0.0, -1.0));


	float AB = LineLenght(A, B);
	float BC = LineLenght(B, C);
	float CA = LineLenght(C, A);
	float CD = LineLenght(C, D);
	float DA = LineLenght(D, A);

	//Get circle center coordinates
	float U = 2 * (A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y));
	cv::Point R;
	R.x = ((pow(A.x, 2) + pow(A.y, 2))*(B.y - C.y) + (pow(B.x, 2) + pow(B.y, 2))*(C.y - A.y) + (pow(C.x, 2) + pow(C.y, 2))*(A.y - B.y)) / U;
	R.y = ((pow(A.x, 2) + pow(A.y, 2))*(C.x - B.x) + (pow(B.x, 2) + pow(B.y, 2))*(A.x - C.x) + (pow(C.x, 2) + pow(C.y, 2))*(B.x - A.x)) / U;


	//calculate radius without choosing bigges triangle (lets use ABC)

	float halfPerimeter = (AB + BC + CA) / 2;
	float innerCircleRadius = sqrt(((halfPerimeter - AB)*(halfPerimeter - BC)*(halfPerimeter - CA)) / halfPerimeter);
	float radius = (AB*BC*CA) / (4 * innerCircleRadius*halfPerimeter);

	mainCircle[0] = R.x;
	mainCircle[1] = R.y;
	mainCircle[2] = radius;
	return mainCircle;
}

float CircleDetector::LineLenght(cv::Point A, cv::Point B)
{
	return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
}

cv::Point CircleDetector::GetEdgePoint(cv::Point startPoint, cv::Vec2f direction)
{
	int streakCounter = 0;
	int streakAccept = 20;
	float searchStep = 1;
	cv::Point edgePoint;
	cv::Point edgeCandidate;
	edgePoint = startPoint;
	edgeCandidate = startPoint;

	while (streakCounter < streakAccept)
	{
		startPoint = edgeCandidate;
		edgeCandidate.x += direction[1] * searchStep;
		edgeCandidate.y += direction[0] * searchStep;
		uchar tmp = src->at<uchar>(edgeCandidate);
		if (src->at<uchar>(edgeCandidate) < tresholdColor)
		{
			streakCounter++;
			if (streakCounter >= streakAccept) {
				edgePoint = edgeCandidate;
				break;
			}

		}
		else
		{
			streakCounter = 0;
		}
	}

	return edgePoint;
}
