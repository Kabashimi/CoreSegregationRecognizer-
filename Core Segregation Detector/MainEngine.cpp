#include "MainEngine.h"


MainEngine::MainEngine()
{
	originalImage = gcnew System::Drawing::Bitmap(1, 1);
	editedImage = gcnew System::Drawing::Bitmap(1, 1);
	filePath = gcnew System::String("");
	originalImageReady = false;
	editedImageReady = false;
	calculationsReady = false;
	segregationSize = 0.0;
	segregationIntensity = 0.0;
	outerRingMeanColor = 0.0;
	segregationTresholdColor = 0;
}

MainEngine::MainEngine(System::String^ path)
{
	originalImage = gcnew System::Drawing::Bitmap(1, 1);
	editedImage = gcnew System::Drawing::Bitmap(1, 1);
	filePath = gcnew System::String(path);
	originalImageReady = false;
	editedImageReady = false;
	calculationsReady = false;
	segregationSize = 0.0;
	segregationIntensity = 0.0;
	outerRingMeanColor = 0.0;
	segregationTresholdColor = 0;
}



void MainEngine::RunCalculation()
{

	//load image
	ImageUtility^ imgUtility = gcnew ImageUtility();
	System::String^ tmpPath = filePath;
	std::string path = msclr::interop::marshal_as<std::string>(tmpPath);
	cv::Mat src = imgUtility->ImageLoad(path);

	originalImage = imgUtility->DrawBitmap(src);
	originalImageReady = true;

	cv::Mat src_gray;
	cv::Mat hist;

	/// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Prepare histogram
	hist = DrawHistogram(src_gray);

	CircleDetector circleDetector(src_gray, hist);
	//Vec3f biggestCircle2 = DetectCircle(src_gray);
	cv::Vec3f biggestCircle = circleDetector.DetectCircle();


	///// Draw the circles detected
	DrawCircle(src, biggestCircle);


	//Perform calculations:	
	cv::Point circleCenter = cv::Point(biggestCircle[0], biggestCircle[1]);
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

	highestColor = 0;
	lowestColor = 255;

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

	outerRingMeanColor = outerRingColorSum / outerRingSegmentsCounter;
	//std::cout << "Mean color: " << outerRingMeanColor << endl;
	//std::cout << "Highest color: " << highestColor << endl;
	//std::cout << "Lowest color: " << lowestColor << endl;

	float lowestToMeanColor = outerRingMeanColor - lowestColor;
	//std::vector<std::vector<Cell> > dataGrid;
	List<List<Cell^>^>^ dataGrid = gcnew List<List<Cell^>^>;
	List<Cell^>^ tmpDataRow = gcnew List<Cell^>;
	int circleSegmentsNumber = 0;
	int outerRingCellsNumber = 0;

	for (float x = x0; x < limx; x += sx) {

		for (float y = y0; y < limy; y += sy) {
			Cell^ tmpCell = gcnew Cell();
			tmpCell->x = x;
			tmpCell->y = y;
			tmpCell->xSpan = sx;
			tmpCell->ySpan = sy;
			segmentCenterX = x + sx / 2;
			segmentCenterY = y + sy / 2;
			tmpCell->distanceToCenter = CalcDistance(circleCenter.x, circleCenter.y, segmentCenterX, segmentCenterY);
			if (tmpCell->distanceToCenter > excludeRange) {
				//tmpDataRow.push_back(tmpCell);
				tmpDataRow->Add(tmpCell);
				continue;
			}
			else
			{

				circleSegmentsNumber++;
				int avgColor = CalcAvgColor(src_gray, x, y, sx, sy);
				tmpCell->value = avgColor;
				tmpCell->active = true;
				if (avgColor < outerRingMeanColor - lowestToMeanColor * 0.8) {
					rectangle(src, cv::Point(x, y), cv::Point(x + sx, y + sy), cv::Scalar(0, 0, 200), CV_FILLED, 8, 0);
				}
				else if (avgColor < outerRingMeanColor - lowestToMeanColor * 0.6) {
					rectangle(src, cv::Point(x, y), cv::Point(x + sx, y + sy), cv::Scalar(0, 100, 200), CV_FILLED, 8, 0);
				}
				else if (avgColor < outerRingMeanColor - lowestToMeanColor * 0.4) {
					rectangle(src, cv::Point(x, y), cv::Point(x + sx, y + sy), cv::Scalar(0, 200, 200), CV_FILLED, 8, 0);
				}
				else {
					rectangle(src, cv::Point(x, y), cv::Point(x + sx, y + sy), cv::Scalar(avgColor, avgColor, avgColor), CV_FILLED, 8, 0);
				}
				if (tmpCell->distanceToCenter > meanRange)
				{
					//circleSegmentsNumber++;
					outerRingCellsNumber++;
					rectangle(src, cv::Point(x, y), cv::Point(x + sx, y + sy), cv::Scalar(outerRingMeanColor, outerRingMeanColor, outerRingMeanColor), CV_FILLED, 8, 0);
				}

			}
			tmpDataRow->Add(tmpCell);
		}
		dataGrid->Add(gcnew List<Cell^>(tmpDataRow));
		tmpDataRow->Clear();
	}

	cv::Mat src2 = src.clone();
	DrawGrid(src2, dataGrid, outerRingMeanColor);

	cv::Mat src3 = src.clone();
	double percent = 0.5;
	int tresholdColor = (percent*(highestColor - lowestColor)) + lowestColor;
	//int tresholdAutomataValue = outerRingMeanColor - lowestToMeanColor * 0.3;
	Automata^ automata = gcnew Automata(dataGrid, meanRange);
	dataGrid = automata->runNaiveEvolution(tresholdColor, 2);
	dataGrid = automata->runNaiveEvolution(tresholdColor, 1);

	List<List<Cell^>^>^ previousDataGrid = gcnew List<List<Cell^>^>;
	cv::Mat previousSrc3 = src3.clone();

	while (automata->outerRingActiveCellsNumber > 10)
	{
		previousDataGrid = dataGrid;
		previousSrc3 = src3.clone();
		cv::Mat src3 = src.clone();
		percent -= 0.05;
		tresholdColor = (percent*(highestColor - lowestColor)) + lowestColor;
		automata = gcnew Automata(dataGrid, meanRange);
		dataGrid = automata->runNaiveEvolution(tresholdColor, 2);
		dataGrid = automata->runNaiveEvolution(tresholdColor, 1);
	}


	DrawGrid(src3, dataGrid);



	editedImage = imgUtility->DrawBitmap(src3);
	editedImageReady = true;

	float segregationSegmentsCounter = 0;
	float segregationValueSum = 0;

	for (int i = 0; i < dataGrid->Count; i++) {
		List<Cell^>^ dataRow = dataGrid[i];
		for (int j = 0; j < dataRow->Count; j++) {
			if (dataRow[j]->automatonActive) {
				segregationSegmentsCounter++;
				segregationValueSum += dataRow[j]->value;
			}
		}
	}

	segregationTresholdColor = tresholdColor;

	segregationSize = segregationSegmentsCounter / circleSegmentsNumber;
	segregationIntensity = (outerRingMeanColor - (segregationValueSum / segregationSegmentsCounter)) / (highestColor - lowestColor);

	std::cout << "Segregation size: " << segregationSize << "%" << std::endl;
	std::cout << "Segregation mean value: " << segregationValueSum / segregationSegmentsCounter << std::endl;

	//ShowImage(src3, "Wynik3");

	FuzzyMachine fuzzy(0.2, 0.3, 0.002, 0.006);
	fuzzy.CalculateSegregationClass(segregationSize, segregationIntensity);

	calculationsReady = true;



	/*cv::namedWindow("Wynik 3", CV_WINDOW_AUTOSIZE);
	imshow("Wynik 3", src3);*/

	//throw gcnew System::NotImplementedException();
}

void MainEngine::SetPath(System::String^ path)
{
	filePath = gcnew System::String(path);
}

double MainEngine::getSegregationSize()
{
	return ceil(segregationSize*10000.0) / 10000.0;
}

double MainEngine::getSegregationIntensity()
{
	return ceil(segregationIntensity*10000.0) / 10000.0;
}

int MainEngine::getMinimalColorValue()
{
	return lowestColor;
}

int MainEngine::getMaximalColorValue()
{
	return highestColor;
}

double MainEngine::getOuterRingMeanValue()
{
	return ceil(outerRingMeanColor*10000.0) / 10000.0;
}

int MainEngine::getSegregationTresholdColorValue()
{
	return segregationTresholdColor;
}

cv::Mat MainEngine::DrawHistogram(cv::Mat src_gray)
{
	bool uniform = true;
	bool accumulate = false;

	cv::Mat hist;
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };

	/// Compute the histograms:
	calcHist(&src_gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

	normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		std::cout << "value = " << hist.at<float>(i) << std::endl;
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);
	}
	std::cout << "SUCCESS\n";

	/// Display
	/*cv::namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);*/
	return hist;
}



void MainEngine::DrawCircle(cv::Mat src, cv::Vec3f circleVec) {
	cv::Scalar colorCenter = cv::Scalar(0, 255, 255);
	cv::Scalar colorOutbound = cv::Scalar(0, 0, 255);
	cv::Point center(cvRound(circleVec[0]), cvRound(circleVec[1]));
	int radius = cvRound(circleVec[2]);
	// circle center
	circle(src, center, 3, colorCenter, -1, 8, 0);
	// circle outline
	circle(src, center, radius, colorOutbound, 3, 8, 0);
}

float MainEngine::CalcDistance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float MainEngine::CalcAvgColor(cv::Mat src, float x, float y, float sx, float sy) {
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

void MainEngine::DrawGrid(cv::Mat src, List<List<Cell^>^>^ dataGrid, float tresholdValue) {
	for (int i = 0; i < dataGrid->Count; i++) {
		List<Cell^>^ dataRow = dataGrid[i];
		for (int j = 0; j < dataRow->Count; j++) {
			if (dataRow[j]->value == 0) {
				continue;
			}
			if (dataRow[j]->value < tresholdValue) {
				cv::Scalar color = cv::Scalar(200, 0, 200);
				rectangle(src, cv::Point(dataRow[j]->x, dataRow[j]->y), cv::Point(dataRow[j]->x + dataRow[j]->xSpan, dataRow[j]->y + dataRow[j]->ySpan), color, CV_FILLED, 8, 0);
			}
		}
	}
}

void MainEngine::DrawGrid(cv::Mat src, List<List<Cell^>^>^ dataGrid) {
	for (int i = 0; i < dataGrid->Count; i++) {
		List<Cell^>^ dataRow = dataGrid[i];
		for (int j = 0; j < dataRow->Count; j++) {
			if (dataRow[j]->automatonActive) {
				cv::Scalar color = cv::Scalar(200, 200, 0);
				rectangle(src, cv::Point(dataRow[j]->x, dataRow[j]->y), cv::Point(dataRow[j]->x + dataRow[j]->xSpan, dataRow[j]->y + dataRow[j]->ySpan), color, CV_FILLED, 8, 0);
			}
		}
	}
}

