#include "pch.h"
#include "CircleDetector.h"


CircleDetector::CircleDetector(Mat src, Mat hist)
{
	float prevValue = 0;
	float value;
	bool passedMaximum = false;
	int minimum;

	//find edge color value - between circle and outer space
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

	this->src = src;
	this->hist = hist;
	tresholdColor = minimum;
}


CircleDetector::~CircleDetector()
{
}

Vec3f CircleDetector::DetectCircle()
{
	Vec3f mainCircle;
	cv::Point center;

	//Get center point
	center.x = src.cols / 2;
	center.y = src.rows / 2;
	if (src.at<float>(center) < tresholdColor) {
		std::cout << "ERROR: Center point is ot inside circle\n";
	}

	//Get 4 point on circle edge
	Point A = GetEdgePoint(center, Vec2f(1.0, 0.0));
	Point B = GetEdgePoint(center, Vec2f(-1.0, 0.0));
	Point C = GetEdgePoint(center, Vec2f(0.0, 1.0));
	Point D = GetEdgePoint(center, Vec2f(0.0, -1.0));

	float AB = norm((B.y - A.y) / (B.x - A.x));
	float BC = norm((C.y - B.y) / (C.x - B.x));
	float CA = norm((C.y - A.y) / (C.x - A.x));
	float CD = norm((D.y - C.y) / (D.x - C.x));
	float DA = norm((A.y - D.y) / (A.x - C.x));

	//Get circle center coordinates
	float U = 2 * (A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y));
	Point R;
	R.x = ((pow(A.x, 2) + pow(A.y, 2))*(B.y - C.y) + (pow(B.x, 2) + pow(B.y, 2))*(C.y - A.y) + (pow(C.x, 2) + pow(C.y, 2))*(A.y - B.y))/U;
	R.x = ((pow(A.x, 2) + pow(A.y, 2))*(B.x - C.x) + (pow(B.x, 2) + pow(B.y, 2))*(C.x - A.x) + (pow(C.x, 2) + pow(C.y, 2))*(A.x - B.x))/U;


	//calculate radius without choosing bigges triangle (lets use ABC)

	float halfPerimeter = (AB+BC+CA)/2
	float innerCircleRadius = sqrt(( (halfPerimeter-AB)*(halfPerimeter-BC)*(halfPerimeter-CA) )/halfPerimeter);
	float radius = (AB*BC*CA)/(4*innerCircleRadius*halfPerimeter);


	return mainCircle;
}

Point CircleDetector::GetEdgePoint(Point startPoint, Vec2f direction)
{
	int streakCounter = 0;
	int streakAccept = 100;
	float searchStep = 1;
	Point edgePoint;
	Point edgeCandidate;
	edgePoint = startPoint;
	edgeCandidate = startPoint;

	while (streakCounter < streakAccept)
	{
		startPoint = edgeCandidate;
		edgeCandidate.x += direction[1] * searchStep;
		edgeCandidate.y += direction[0] * searchStep;
		if(src.at<float>(edgeCandidate) < tresholdColor)
		{
			streakCounter++;
		}
		else
		{
				streakCounter = 0;
		}
	}

	return edgePoint;
}
