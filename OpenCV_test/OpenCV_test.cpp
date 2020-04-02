// OpenCV_test.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <cmath>
#include "Cell.h"
#include "Automaton.h"
#include "FuzzyMachine.h"
#include "CircleDetector.h"
#include<fstream>


using namespace cv;
using namespace std;

Mat LoadImage(String fileName) {
	std::cout << "Image load: ";
	Mat src, src_gray;
	src = imread(fileName, CV_LOAD_IMAGE_COLOR);

	if (!src.data)
	{
		std::cout << "FAILURE\n";
		exit(1);
	}

	std::cout << "SUCCESS\n";
	return src;
}

Mat DrawHistogram(Mat src_gray) {

	bool uniform = true;
	bool accumulate = false;

	Mat hist;
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };

	/// Compute the histograms:
	std::cout << "Histogram calculation: ";
	calcHist(&src_gray, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
	std::cout << "SUCCESS\n";

	// Draw the histograms for B, G and R
	std::cout << "Histogram draw: ";
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		std::cout << "value = " << hist.at<float>(i) << endl;
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	std::cout << "SUCCESS\n";

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);
	return hist;
}

int GetCircleLeft(Mat src, int minimum, int streakAccept) {
	int streakCounter = 0;
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (src.at<uchar>(i, j) > minimum) {
				streakCounter++;
				if (streakCounter == streakAccept) {
					return i;
				}
			}
			else {
				streakCounter = 0;
			}
		}
	}
}

int GetCircleRight(Mat src, int minimum, int streakAccept) {
	int streakCounter = 0;
	for (int i = src.rows - 1; i > 0; i--) {
		for (int j = 0; j < src.cols; j++) {
			if (src.at<uchar>(i, j) > minimum) {
				streakCounter++;
				if (streakCounter == streakAccept) {
					return i;
				}
			}
			else {
				streakCounter = 0;
			}
		}
	}
}

int GetCircleTop(Mat src, int minimum, int streakAccept) {
	int streakCounter = 0;
	for (int j = 0; j < src.cols; j++) {
		for (int i = 0; i < src.rows; i++) {
			if (src.at<uchar>(i, j) > minimum) {
				streakCounter++;
				if (streakCounter == streakAccept) {
					return j;
				}
			}
			else {
				streakCounter = 0;
			}
		}
	}
}

int GetCircleBottom(Mat src, int minimum, int streakAccept) {
	int streakCounter = 0;
	for (int j = src.cols - 1; j > 0; j--) {
		for (int i = 0; i < src.rows; i++) {
			if (src.at<uchar>(i, j) > minimum) {
				streakCounter++;
				if (streakCounter == streakAccept) {
					return j;
				}
			}
			else {
				streakCounter = 0;
			}
		}
	}
}

Vec3f DetectCircle(Mat src, Mat hist) {
	Vec3f circle;
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

	int streakCounter = 0;
	int streakAccept = 500;

	int circleLeft = GetCircleLeft(src, minimum, streakAccept);
	int circleTop = GetCircleTop(src, minimum, streakAccept);
	int circleRight = GetCircleRight(src, minimum, streakAccept);
	int circleBottom = GetCircleBottom(src, minimum, streakAccept);

	circle[0] = circleTop + (circleBottom - circleTop) / 2;
	circle[1] = circleLeft + (circleRight - circleLeft) / 2;
	circle[2] = (circleRight - circleLeft) / 2;

	return circle;
}

Vec3f DetectCircle(Mat src_gray) {
	Mat src_gray_blur;
	vector<Vec3f> circles;
	Vec3f biggestCircle;

	/// Reduce the noise so we avoid false circle detection
	std::cout << "Circles detection: ";
	GaussianBlur(src_gray, src_gray_blur, Size(9, 9), 2, 2);

	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray_blur, circles, CV_HOUGH_GRADIENT, 1, src_gray_blur.rows / 8, 80, 40, 0, 0);
	std::cout << "SUCCESS\n";
	std::cout << "Circles number: " << circles.size() << endl;

	biggestCircle[0] = 0;
	biggestCircle[1] = 0;
	biggestCircle[2] = 0;
	for (size_t i = 0; i < circles.size(); i++)
	{
		if (circles[i][2] > biggestCircle[2])
		{
			biggestCircle[0] = circles[i][0];
			biggestCircle[1] = circles[i][1];
			biggestCircle[2] = circles[i][2];
		}
	}
	return biggestCircle;
}

void DrawCircle(Mat src, Vec3f circleVec) {
	Scalar colorCenter = Scalar(0, 255, 255);
	Scalar colorOutbound = Scalar(0, 0, 255);
	Point center(cvRound(circleVec[0]), cvRound(circleVec[1]));
	int radius = cvRound(circleVec[2]);
	// circle center
	circle(src, center, 3, colorCenter, -1, 8, 0);
	// circle outline
	circle(src, center, radius, colorOutbound, 3, 8, 0);
}

void DrawCircles(Mat src, vector<Vec3f> circles) {
	for (size_t i = 0; i < circles.size(); i++)
	{
		DrawCircle(src, circles[i]);
	}
}

Mat CroppImage(Mat src, Vec3f biggestCircle) {
	std::cout << "Cropping image: ";
	int left_top_corner_x = biggestCircle[0] - biggestCircle[2];
	int left_top_corner_y = biggestCircle[1] - biggestCircle[2];
	int right_bottom_corner_x = biggestCircle[0] + biggestCircle[2];
	int right_bottom_corner_y = biggestCircle[1] + biggestCircle[2];
	cv::Rect myROI(left_top_corner_x, left_top_corner_y, biggestCircle[2] * 2, biggestCircle[2] * 2);
	cv::Mat cropped = src(myROI);
	std::cout << "SUCCESS\n";
	return cropped;
}

void ShowImage(Mat src, String windowName) {
	// Resize image by half
	std::cout << "Image resize: ";
	Mat resized;
	resize(src, resized, Size(), 0.5, 0.5);
	std::cout << "SUCCESS\n";

	///// Show your results
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	imshow(windowName, resized);
}

float CalcDistance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float CalcAvgColor(Mat src, float x, float y, float sx, float sy) {
	float sum = 0;
	float pixelsNumber = 0;
	for (float i = x; i < x + sx; i++) {
		for (float j = y; j < y + sy; j++) {
			sum += src.at<uchar>(static_cast<int>(j), static_cast<int>(i));
			pixelsNumber++;

		}
	}

	return sum / pixelsNumber;
}

void DrawGrid(Mat src, vector<vector<Cell>> dataGrid) {
	for (int i = 0; i < dataGrid.size(); i++) {
		for (int j = 0; j < dataGrid[i].size(); j++) {
			if (dataGrid[i][j].automatonActive) {
				Scalar color = Scalar(200, 200, 0);
				rectangle(src, Point(dataGrid[i][j].x, dataGrid[i][j].y), Point(dataGrid[i][j].x + dataGrid[i][j].xSpan, dataGrid[i][j].y + dataGrid[i][j].ySpan), color, CV_FILLED, 8, 0);
			}
		}
	}
}

void DrawGrid(Mat src, vector<vector<Cell>> dataGrid, float tresholdValue) {
	for (int i = 0; i < dataGrid.size(); i++) {
		for (int j = 0; j < dataGrid[i].size(); j++) {
			if (dataGrid[i][j].value == 0) {
				continue;
			}
			if (dataGrid[i][j].value < tresholdValue) {
				Scalar color = Scalar(200, 0, 200);
				rectangle(src, Point(dataGrid[i][j].x, dataGrid[i][j].y), Point(dataGrid[i][j].x + dataGrid[i][j].xSpan, dataGrid[i][j].y + dataGrid[i][j].ySpan), color, CV_FILLED, 8, 0);
			}
		}
	}
}

void mainCalcFunction(int photoNumber, bool writeToFile) {

	std::cout << endl << endl;
	std::cout << "Open image: " << photoNumber << endl;
	//Load image
	String photoName = "new_images/2-";
	//String photoName = "images/";
	photoName += std::to_string(photoNumber);
	photoName += ".jpg";
	Mat src = LoadImage(photoName);
	Mat src_gray;
	Mat hist;

	/// Convert it to gray
	std::cout << "Convert to gray: ";
	cvtColor(src, src_gray, CV_BGR2GRAY);
	std::cout << "SUCCESS\n";

	// Prepare histogram
	hist = DrawHistogram(src_gray);
	
	//Detect circle
	//Vec3f biggestCircle = DetectCircle(src_gray, hist);

	CircleDetector circleDetector(src_gray, hist);
	//Vec3f biggestCircle2 = DetectCircle(src_gray);
	Vec3f biggestCircle = circleDetector.DetectCircle();
	

	///// Draw the circles detected
	std::cout << "Drawing circle: ";
	DrawCircle(src, biggestCircle);
	std::cout << "SUCCESS\n";

	//Perform calculations:			//////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Circle size: " << biggestCircle[0] << ':' << biggestCircle[1] << ':' << biggestCircle[2] << endl;

	Point circleCenter = Point(biggestCircle[0], biggestCircle[1]);
	float radius = biggestCircle[2];

	float segmentsNumber = 100;
	float sx = (radius * 2) / segmentsNumber;
	float sy = (radius * 2) / segmentsNumber;
	float x0 = circleCenter.x - radius;
	float y0 = circleCenter.y - radius;
	float limx = circleCenter.x + radius;
	float limy = circleCenter.y + radius;
	float segmentCenterX;
	float segmentCenterY;
	float distanceToCenter;

	float excludeRange = radius * 0.9;
	float meanRange = radius * 0.7;

	int outerRingColorSum = 0;
	int outerRingSegmentsCounter = 0;

	int highestColor = 0;
	int lowestColor = 255;


	for (float x = x0; x < limx; x += sx) {
		for (float y = y0; y < limy; y += sy) {
			segmentCenterX = x + sx / 2;
			segmentCenterY = y + sy / 2;
			distanceToCenter = CalcDistance(circleCenter.x, circleCenter.y, segmentCenterX, segmentCenterY);
			if (distanceToCenter > excludeRange) {
				continue;
			}
			else if (distanceToCenter > meanRange)
			{
				//rectangle(src, Point(x, y), Point(x + sx, y + sy), Scalar(200, 200, 0), CV_FILLED, 8, 0);
				outerRingColorSum += CalcAvgColor(src_gray, x, y, sx, sy);
				outerRingSegmentsCounter++;
			}
			else
			{
				int avgColor = CalcAvgColor(src_gray, x, y, sx, sy);
				if (avgColor > highestColor) {
					highestColor = avgColor;
				}
				if (avgColor < lowestColor) {
					lowestColor = avgColor;
				}
			}
		}
	}

	float outerRingMeanColor = outerRingColorSum / outerRingSegmentsCounter;
	std::cout << "Mean color: " << outerRingMeanColor << endl;
	std::cout << "Highest color: " << highestColor << endl;
	std::cout << "Lowest color: " << lowestColor << endl;

	float lowestToMeanColor = outerRingMeanColor - lowestColor;
	vector<vector<Cell> > dataGrid;
	vector<Cell> tmpDataRow;


	for (float x = x0; x < limx; x += sx) {

		for (float y = y0; y < limy; y += sy) {
			Cell tmpCell;
			tmpCell.x = x;
			tmpCell.y = y;
			tmpCell.xSpan = sx;
			tmpCell.ySpan = sy;
			segmentCenterX = x + sx / 2;
			segmentCenterY = y + sy / 2;
			distanceToCenter = CalcDistance(circleCenter.x, circleCenter.y, segmentCenterX, segmentCenterY);
			if (distanceToCenter > excludeRange) {
				tmpDataRow.push_back(tmpCell);
				continue;
			}
			else if (distanceToCenter > meanRange)
			{

				rectangle(src, Point(x, y), Point(x + sx, y + sy), Scalar(outerRingMeanColor, outerRingMeanColor, outerRingMeanColor), CV_FILLED, 8, 0);
			}
			else
			{
				int avgColor = CalcAvgColor(src_gray, x, y, sx, sy);
				tmpCell.value = avgColor;
				tmpCell.active = true;
				if (avgColor < outerRingMeanColor - lowestToMeanColor * 0.8) {
					rectangle(src, Point(x, y), Point(x + sx, y + sy), Scalar(0, 0, 200), CV_FILLED, 8, 0);
				}
				else if (avgColor < outerRingMeanColor - lowestToMeanColor * 0.6) {
					rectangle(src, Point(x, y), Point(x + sx, y + sy), Scalar(0, 100, 200), CV_FILLED, 8, 0);
				}
				else if (avgColor < outerRingMeanColor - lowestToMeanColor * 0.4) {
					rectangle(src, Point(x, y), Point(x + sx, y + sy), Scalar(0, 200, 200), CV_FILLED, 8, 0);
				}
				else {
					rectangle(src, Point(x, y), Point(x + sx, y + sy), Scalar(avgColor, avgColor, avgColor), CV_FILLED, 8, 0);
				}

			}
			tmpDataRow.push_back(tmpCell);
		}
		dataGrid.push_back(tmpDataRow);
		tmpDataRow.clear();
	}

	Mat src2 = src.clone();
	DrawGrid(src2, dataGrid, outerRingMeanColor);

	Mat src3 = src.clone();
	int tresholdAutomataValue = outerRingMeanColor - lowestToMeanColor * 0.3;
	Automaton automata = Automaton(dataGrid);
	dataGrid = automata.runNaiveEvolution(tresholdAutomataValue, 2);
	dataGrid = automata.runNaiveEvolution(tresholdAutomataValue, 1);
	DrawGrid(src3, dataGrid);

	float segregationSegmentsCounter = 0;
	float segregationValueSum = 0;

	for (int i = 0; i < dataGrid.size(); i++) {
		for (int j = 0; j < dataGrid[i].size(); j++) {
			if (dataGrid[i][j].automatonActive) {
				segregationSegmentsCounter++;
				segregationValueSum += dataGrid[i][j].value;
			}
		}
	}

	double segregationSize = segregationSegmentsCounter / (dataGrid.size() * dataGrid[0].size());
	double proportionValue = (outerRingMeanColor - (segregationValueSum / segregationSegmentsCounter)) / (highestColor - lowestColor);

	std::cout << "Segregation size: " << segregationSegmentsCounter / (dataGrid.size() * dataGrid[0].size()) << "%" << endl;
	std::cout << "Segregation mean value: " << segregationValueSum / segregationSegmentsCounter << endl;

	ShowImage(src3, "Wynik3");

	FuzzyMachine fuzzy(0.2, 0.3, 0.002, 0.006);
	fuzzy.CalculateSegregationClass(segregationSize, proportionValue);


	if (writeToFile) {
		ofstream resultFile;
		resultFile.open("results.csv", std::ios::app);
		//Mean color
		resultFile << outerRingMeanColor << ';';
		//Highest color
		resultFile << highestColor << ';';
		//Lowest color
		resultFile << lowestColor << ';';
		//segregation size %
		resultFile << segregationSize << ';';
		// segregation mean value
		resultFile << segregationValueSum / segregationSegmentsCounter << ';';
		//proportion value
		resultFile << proportionValue << ';';
		resultFile << endl;

		resultFile.close();
	}

	waitKey(0);
}

void HistFunction(int photoNumber, bool writeToFile) {

	std::cout << endl << endl;
	std::cout << "Open image: " << photoNumber << endl;
	//Load image
	//String photoName = "new_images/1-";
	String photoName = "images/";
	photoName += std::to_string(photoNumber);
	photoName += ".jpg";
	Mat src = LoadImage(photoName);
	Mat src_gray;
	Mat hist;

	/// Convert it to gray
	std::cout << "Convert to gray: ";
	cvtColor(src, src_gray, CV_BGR2GRAY);
	std::cout << "SUCCESS\n";

	// Prepare histogram
	hist = DrawHistogram(src_gray);
	waitKey(0);
}

int main()
{

	mainCalcFunction(1, false);
	//HistFunction(1, false);

	/*for (int i = 1; i < 16; i++) {
		mainCalcFunction(i, true);
	}*/

	//int k, l;
	//Scalar color = Scalar(250, 250, 200);
	//k = 24;
	//l = 2373;
	//rectangle(src, Point(dataGrid[k][l].x, dataGrid[k][l].y), Point(dataGrid[k][l].x + dataGrid[k][l].xSpan, dataGrid[k][l].y + dataGrid[k][l].ySpan), color, CV_FILLED, 8, 0);
	//k = 25;
	//l = 2373;
	//rectangle(src, Point(dataGrid[k][l].x, dataGrid[k][l].y), Point(dataGrid[k][l].x + dataGrid[k][l].xSpan, dataGrid[k][l].y + dataGrid[k][l].ySpan), color, CV_FILLED, 8, 0);
	//k = 26;
	//l = 2373;
	//rectangle(src, Point(dataGrid[k][l].x, dataGrid[k][l].y), Point(dataGrid[k][l].x + dataGrid[k][l].xSpan, dataGrid[k][l].y + dataGrid[k][l].ySpan), color, CV_FILLED, 8, 0);
	//k = 27;
	//l = 2373;
	//rectangle(src, Point(dataGrid[k][l].x, dataGrid[k][l].y), Point(dataGrid[k][l].x + dataGrid[k][l].xSpan, dataGrid[k][l].y + dataGrid[k][l].ySpan), color, CV_FILLED, 8, 0);

	//cvtColor(cropped, cropped, CV_BGR2GRAY);

	///// Show your results
	//namedWindow("Test image", CV_WINDOW_AUTOSIZE);
	//imshow("Test image", cropped);



	//std::cout << "Setting outbound to 0: ";
	//int centerX = biggestCircle[2];
	//int centerY = biggestCircle[2];
	//for (int y = 0; y < src.rows; y++)
	//{
	//	for (int x = 0; x < src.cols; x++)
	//	{
	//		double point_distance = sqrt(pow(centerX - x, 2) + pow(centerY - y, 2));		//CHANGE TO SQRTDISTANCE
	//		//int color = (int)cropped.at<uchar>(x, y);

	//		if (point_distance >= biggestCircle[2])
	//		{
	//			//cout << "distance " << point_distance<< endl;
	//			//color = 0;
	//			//cropped.at<uchar>(x, y) = 255;
	//		}
	//	}
	//}
	//std::cout << "SUCCESS\n";


	//END							////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ShowImage(src, "Wynik");
	//ShowImage(src2, "Wynik2");
	//ShowImage(src3, "Wynik3");

	std::cout << "Finished!\n";

	waitKey(0);
	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
